#include "pdt.h"
void init_paging(void * pdt)
{
    load_pdt(pdt);
    enable_paging();
}

void init_pdt(void * pdt_p)
{
    struct pde * pdt = (struct pde *) pdt_p;
    struct pde def;

    def.accessed           = 0;
    def.present            = 0;
    def.user               = 0;
    def.write              = 1;
    def.size               = 0;
    def.cache_disabled     = 0;
    def.sysinfo            = 0;
    def.nullbit            = 0;
    def.wrtie_through      = 0;
    def.page_table_address = 0;
    def.global             = 0;

    for (int i = 0; i < 1024; i++) {
        // Page directory set as : Kernel, Writable, not present
        pdt[i] = def;
    }
}

bool insert_page_table(void * pdt_p, struct pde page_dir_entry)
{
    struct pde * pdt = (struct pde *) pdt_p;
    int i = 0;

    while (pdt[i].sysinfo != 0 && i < 1024) { // find an unused entry
        i++;
    }
    if (i < 1024)                 // if there's still an available entry
        pdt[i] = page_dir_entry;  // set it
    return i < 1024;
}

bool insert_page_in_pdt(void * pdt_p, struct pte page_entry)
{
    struct pde * pdt = (struct pde *) pdt_p;
    int i         = 0;
    bool inserted = false;

    while (pdt[i].sysinfo != 0 && i < 1024) {                                              // on all tables
        inserted = insert_page((void *) (pdt[i].page_table_address * 0x1000), page_entry); // try to insert
    }
    if (i < 1024) {                               // if there's an unused entry
        void * pt = (void *) (palloc() * 0x1000); // allocate a page for a table
        init_pt(pt);                              // initialize it
        inserted = insert_page(pt, page_entry);   // and insert the page in the table
    }

    return inserted;
}

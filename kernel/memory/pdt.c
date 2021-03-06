#include "pdt.h"
extern struct def_vga_screen default_screen;

void init_paging(void * pdt) // loads the PDT and enable paging
{
    load_pdt(pdt);
    enable_paging();
}

void init_pdt(void * pdt_p) // initialises a PDT with blank pages
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

bool insert_page_table(void * pdt_p, struct pde page_dir_entry) // inserts an entry in the PDT
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

bool insert_page_in_pdt(void * pdt_p, struct pte page_entry, bool from_latest) // inserts a page entry in the PDT finding or creating a page directory as needed
{
    struct pde * pdt = (struct pde *) pdt_p;
    int i         = (from_latest) ? last_inserted_page : 0;
    bool inserted = false;

    while (pdt[i].sysinfo != 0 && i < 1024 && !inserted) {                                  // on all tables
        inserted |= insert_page((void *) (pdt[i].page_table_address * 0x1000), page_entry); // try to insert
        i++;
    }
    if (i < 1024 && !inserted) { // if there's an unused entry
        int tab_page = palloc();
        void * pt    = (void *) (tab_page * 0x1000); // allocate a page for a table
        init_pt(pt);                                 // initialize it
        inserted |= insert_page(pt, page_entry);     // and insert the page in the table
        struct pde def;
        def.accessed           = 0;
        def.present            = 1;
        def.user               = 0;
        def.write              = 1;
        def.size               = 0;
        def.cache_disabled     = 0;
        def.sysinfo            = 1;
        def.nullbit            = 0;
        def.wrtie_through      = 0;
        def.page_table_address = tab_page;
        def.global             = 0;
        insert_page_table(pdt_p, def);
        i++;
    }
    if (inserted) { // some weirdness to make page insertion with optimisation work : start search for available page entry 1 earlier
        last_inserted_page = (i - 2 > 0) ? i - 2 : 0;
    }
    return inserted;
} /* insert_page_in_pdt */

void identity_page(void * pdt_p, int number_of_pages) // identity page the first "number of pages" in the pdt passed as argument using insertion technique : slow
{
    for (int page = 0; page < number_of_pages; page++) {
        struct pte def;

        def.accessed         = 0;
        def.present          = 1;
        def.user             = 0;
        def.write            = 1;
        def.reserved         = 0;
        def.reserved2        = 0;
        def.sysinfo          = 1;
        def.dirty            = 0;
        def.physical_address = page; // make the page entry

        insert_page_in_pdt(pdt_p, def, true); // insert it
    }
}

void fast_identity_page(void * pdt_p, int number_of_pages) // identity page the first "number of pages" in the pdt passed as argument using manual creation : fast
{
    struct pde * pdt  = (struct pde *) pdt_p;
    int current_index = -1;
    uint32_t dirtofill;

    for (int page = 0; page < number_of_pages; page++) {
        if (page % 1024 == 0) {         // if we have to create a new directory : do so
            uint32_t newdir = palloc(); // reserve a page for the directory's entries
            struct pde dir;
            dir.accessed           = 0;
            dir.present            = 1;
            dir.user               = 0;
            dir.write              = 1;
            dir.size               = 0;
            dir.cache_disabled     = 0;
            dir.sysinfo            = 1;
            dir.nullbit            = 0;
            dir.wrtie_through      = 0;
            dir.page_table_address = newdir;
            dir.global             = 0;
            current_index++;
            pdt[current_index] = dir;
            dirtofill = newdir;
        }
        struct pte def; // create the page entry
        def.accessed         = 0;
        def.present          = 1;
        def.user             = 0;
        def.write            = 1;
        def.reserved         = 0;
        def.reserved2        = 0;
        def.sysinfo          = 1;
        def.dirty            = 0;
        def.physical_address = page; // the magic here is that the pages are inserted in order and contiguously in the PDT corresponding to the physical pages

        uint32_t addr       = dirtofill * 0x1000 + (sizeof(struct pte) * (page % 1024)); // where to put the page entry
        struct pte * tofill = (struct pte *) addr;
        *tofill = def;
    }
} /* fast_identity_page */

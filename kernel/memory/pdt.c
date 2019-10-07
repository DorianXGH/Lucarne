#include "pdt.h"
extern struct def_vga_screen default_screen;

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
        putchar(&default_screen, (i % 8) + 48);
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

bool insert_page_in_pdt(void * pdt_p, struct pte page_entry, bool from_latest)
{
    struct pde * pdt = (struct pde *) pdt_p;
    int i         = (from_latest) ? last_inserted_page : 0;
    bool inserted = false;

    while (pdt[i].sysinfo != 0 && i < 1024 && !inserted) {                                  // on all tables
        inserted |= insert_page((void *) (pdt[i].page_table_address * 0x1000), page_entry); // try to insert
        i++;
    }
    if (inserted) {
        putchar(&default_screen, '!');
        char a[10];
        prntnum(i, '+', a, 10);
        putstring(&default_screen, a);
    }
    if (i < 1024 && !inserted) { // if there's an unused entry
        int tab_page = palloc();
        void * pt    = (void *) (tab_page * 0x1000); // allocate a page for a table
        init_pt(pt);                                 // initialize it
        inserted |= insert_page(pt, page_entry);     // and insert the page in the table
        if (inserted) putchar(&default_screen, '=');
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
        putchar(&default_screen, '|');
        i++;
    }
    if (inserted) {
        putchar(&default_screen, '_');
        char a[10];
        // prntnum(i, '+', a, 10);
        // putstring(&default_screen, a);
        last_inserted_page = i--;
    }
    return inserted;
} /* insert_page_in_pdt */

void identity_page(void * pdt_p, int number_of_pages)
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
        def.physical_address = page;
        insert_page_in_pdt(pdt_p, def, true);
    }
}

#include "pt.h"
extern struct def_vga_screen default_screen;

void init_pt(void * pt_p)
{
    struct pte * pt = (struct pte *) pt_p;
    struct pte def;

    def.accessed         = 0;
    def.present          = 0;
    def.user             = 0;
    def.write            = 1;
    def.reserved         = 0;
    def.dirty            = 0;
    def.sysinfo          = 0;
    def.reserved2        = 0;
    def.physical_address = 0;

    for (int i = 0; i < 1024; i++) {
        // Page directory set as : Kernel, Writable, not present
        pt[i] = def;
    }
}

bool insert_page(void * pt_p, struct pte page_entry)
{
    struct pte * pt = (struct pte *) pt_p;
    int i = 0;

    while (pt[i].sysinfo != 0 && i < 1024) { // find an unused entry
        i++;
    }
    if (i < 1024) {         // if there's still an available entry
        pt[i] = page_entry; // set it
        // putchar(&default_screen, 'b');
    } else {
        // putchar(&default_screen, 'a');
    }
    return i < 1024;
}

#include "pt.h"

void init_pt(void * pt_p)
{
    struct pte * pt = (struct pte *) pt_p;
    struct pte def;

    def.accessed         = 0;
    def.present          = 0;
    def.user             = 0;
    def.write            = 1;
    def.cached           = 0;
    def.dirty            = 0;
    def.sysinfo          = 0;
    def.nullbit          = 0;
    def.wrtie_through    = 0;
    def.physical_address = 0;
    def.global           = 0;

    for (int i = 0; i < 1024; i++) {
        // Page directory set as : Kernel, Writable, not present
        pt[i] = def;
    }
}

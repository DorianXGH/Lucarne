#include "pdt.h"
void init_paging(void * a)
{
    pdt = (struct pde*)a;
    load_pdt(pdt);
}

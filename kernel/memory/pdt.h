#ifndef PDT_H
#define PDT_H
#include "pt.h"


struct pde {
    bool present : 1;
    bool write : 1;
    bool user : 1;
    bool wrtie_through : 1;
    bool cache_disabled : 1;
    bool accessed : 1;
    bool nullbit : 1;
    bool size : 1;
    bool global : 1;
    char sysinfo : 3;
    int  page_table_address : 20;
} __attribute__((packed));

extern void load_pdt(struct pde *);
extern void enable_paging();

void init_paging(void * a);
void init_pdt(void * a);
void insert_page(void * pdt_p, struct pte);

#endif /* ifndef PDT_H */

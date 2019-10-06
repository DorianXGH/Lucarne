#ifndef PT_H
#define PT_H
struct pte {
    bool present : 1;
    bool write : 1;
    bool user : 1;
    bool wrtie_through : 1;
    bool cached : 1;
    bool accessed : 1;
    bool dirty : 1;
    bool nullbit : 1;
    bool global : 1;
    char sysinfo : 3;
    int  physical_address : 20;
} __attribute__((packed));

void init_pt(void * pt_p);


#endif /* ifndef PT_H */

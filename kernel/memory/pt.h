#ifndef PT_H
#define PT_H
#include <stdbool.h>
#include <stdint.h>
#include "../drivers/screen.h"

struct pte {
    bool    present : 1;
    bool    write : 1;
    bool    user : 1;
    uint8_t reserved : 2;
    bool    accessed : 1;
    bool    dirty : 1;
    uint8_t reserved2 : 2;
    uint8_t sysinfo : 3;
    int     physical_address : 20;
} __attribute__((packed));

void init_pt(void * pt_p);

bool insert_page(void * pt_p, struct pte);

#endif /* ifndef PT_H */

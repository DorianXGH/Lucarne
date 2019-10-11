#ifndef GDT_H
#define GDT_H
#include <stdint.h>
#include <stdbool.h>

enum seg_type {
    CODE,
    DATA,
    TSS
};

struct gde {
    uint16_t limit_a : 16;
    uint16_t base_a : 16;
    uint8_t  base_b : 8;
    bool     accessed : 1;
    bool     RW : 1;
    bool     DC : 1;
    bool     executable : 1;
    bool     descriptor : 1;
    uint8_t  ring : 2;
    bool     present : 1;
    uint8_t  limit_b : 4;
    uint8_t  null : 2;
    bool     bitsize_16_32 : 1;
    bool     granularity : 1;
} __attribute__((packed));

struct gdt {
    uint16_t size : 16;
    uint32_t base : 32;
} __attribute__((packed));

void add_to_gdt(struct gdt * desc, uint32_t base, uint32_t size, uint8_t ring, enum seg_type type);

#endif /* ifndef GDT_H */

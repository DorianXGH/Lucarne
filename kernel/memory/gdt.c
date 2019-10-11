#include "gdt.h"
void add_to_gdt(struct gdt * desc, uint32_t base, uint32_t size, uint8_t ring, enum seg_type type)
{
    struct gde * dt = desc->base;
    struct gde new;

    new.base_a        = base & 0xFFFF;
    new.base_b        = (base >> 16) & 0xFF;
    new.limit_a       = size & 0xFFFF;
    new.limit_b       = (size >> 16) & 0xF;
    new.accessed      = 0;
    new.present       = 1;
    new.RW            = 1;
    new.granularity   = 1;
    new.bitsize_16_32 = 1;
    new.null          = 0;
    new.ring          = ring & 0b11;
    new.DC            = 0;
    switch (type) {
        case CODE:
            new.executable = 1;
            new.descriptor = 1;
            break;
        case DATA:
            new.executable = 0;
            new.descriptor = 1;
            break;
        case TSS:
            new.executable = 0;
            new.descriptor = 0;
            break;
        default:
            new.executable = 0;
            new.descriptor = 1;
            break;
    }
    dt[desc->size + 1] = new;
    desc->size++;
} /* add_to_gdt */

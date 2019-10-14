#include "gdt.h"
void add_to_gdt(struct gdt * desc, uint32_t base, uint32_t size, uint8_t ring, enum seg_type type, int ent)
{
    struct gde * dt = (struct gde *) desc->base;
    struct gde new;

    new.base_a        = base & 0xFFFF;
    new.base_b        = (base >> 16) & 0xFF;
    new.base_c        = (base >> 24) & 0xFF;
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
            new.executable    = 0;
            new.descriptor    = 0;
            new.base_a        = 0;
            new.base_b        = 0;
            new.base_c        = 0;
            new.limit_a       = 0;
            new.limit_b       = 0;
            new.accessed      = 0;
            new.present       = 0;
            new.RW            = 0;
            new.granularity   = 0;
            new.bitsize_16_32 = 0;
            new.null          = 0;
            new.ring          = 0;
            new.DC            = 0;
            break;
    }
    dt[ent]       = new;
    (desc->size) += 8;
} /* add_to_gdt */

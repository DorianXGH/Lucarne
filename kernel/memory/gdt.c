#include "gdt.h"
void add_to_gdt(struct gdt * desc, uint32_t base, uint32_t size, uint8_t ring, enum seg_type type, int ent) // this adds an entry to the GDT : desc : points to
// the beginning of the GDT; base : pointer to the beginning of the new segment; size : size of the new segment in pages; ring : priviledge level of the segment
// type : see enum; ent : which entry (index) do you set
{
    struct gde * dt = (struct gde *) desc->base; // points to the first entry of the table
    struct gde new;                              // the new entry

    // position each part of the arguments in the right location
    new.base_a        = base & 0xFFFF;
    new.base_b        = (base >> 16) & 0xFF;
    new.base_c        = (base >> 24) & 0xFF;
    new.limit_a       = size & 0xFFFF;
    new.limit_b       = (size >> 16) & 0xF;
    new.accessed      = 0;           // is the semgent being accessed by the procesoor
    new.present       = 1;           // is the segment present in memory : yes
    new.RW            = 1;           // readable for code segments and writable for data segments
    new.granularity   = 1;           // limit in pages or in bytes : here, in pages
    new.bitsize_16_32 = 1;           // it's 32 bits
    new.null          = 0;           // this part must be null
    new.ring          = ring & 0b11; // which code level can access it
    new.DC            = 0;           // direction or conforming bit, 0 as we won't use this feature
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
    dt[ent]       = new; // put the new entry in the table
    (desc->size) += 8;   // modify size accordingly
} /* add_to_gdt */

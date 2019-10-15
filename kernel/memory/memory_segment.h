#ifndef MEMORY_SEGMENT_H
#define MEMORY_SEGMENT_H
#include <stdint.h>
#include "../drivers/screen.h"
#include "../util.h"

struct memory_seg_des {
    uint32_t size : 32;
    uint64_t base : 64;
    uint64_t length : 64;
    uint32_t type : 32;
} __attribute__((packed));
struct memory_seg_des * memmap;
int * nummem;

void print_map(struct def_vga_screen * s);


#endif /* ifndef MEMORY_SEGMENT_H */

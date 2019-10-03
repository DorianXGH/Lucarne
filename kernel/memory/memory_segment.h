#ifndef MEMORY_SEGMENT_H
#define MEMORY_SEGMENT_H
#include <stdint.h>

struct memory_seg_des {
    uint64_t base : 64;
    uint64_t length : 64;
    uint32_t type : 32;
    uint32_t extatt : 32;
} __attribute__((packed));
struct memory_seg_des * memmap;
#endif

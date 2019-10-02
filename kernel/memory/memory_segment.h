#ifndef MEMORY_SEGMENT_H
#define MEMORY_SEGMENT_H

struct memory_seg_des {
    long int base;
    long int length;
    int type;
    int extatt;
} __attribute__((packed));
struct memory_seg_des * memmap;
#endif

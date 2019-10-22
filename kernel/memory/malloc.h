#ifndef MALLOC_H
#define MALLOC_H
#include <stdint.h>

struct alloc_seg {
    uint32_t ptr;
    uint32_t sz;
} __attribute__((packed));

alloc_seg * alloc_seg_lst;
int max_alloc_seg = 2048;

void * kmalloc(size_t s);

#endif /* ifndef MALLOC_H */

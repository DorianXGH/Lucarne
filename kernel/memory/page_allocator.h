#ifndef PAGE_ALLOCATOR_H
#define PAGE_ALLOCATOR_H
#include "memory_segment.h"
#include <stdint.h>

extern memory_seg_des * memmap;
extern int * memnum;

int next_available;
int max_page;
uint8_t * page_tracker;

int palloc();
void pfree(int pagenum);
void init_page_alloc();


#endif

#ifndef PAGE_ALLOCATOR_H
#define PAGE_ALLOCATOR_H
#include "memory_segment.h"
#include <stdint.h>
#include <stdbool.h>
#include "../drivers/screen.h"

extern struct memory_seg_des * memmap;
extern int * nummem;

int next_available;
int max_page;
uint8_t * page_tracker;

int palloc();
int palloc_n(int);
void pfree(int pagenum);
void preserve(int pagenum);
void init_page_alloc();
bool pstatus(int i);
void find_next_free();

#endif /* ifndef PAGE_ALLOCATOR_H */

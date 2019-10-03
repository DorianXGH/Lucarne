#include "page_allocator.h"
int palloc()
{
    int p = next_available;
    for(int i = p + 1;
        i <= max_page &&
        (page_tracker[i/8]>>(i%8))&1;
        i++)
    {
        next_available = i;
    }
    return p;
}
void free(int pagenum)
{
    int8_t a = page_tracker[pagenum/8];
    int r = pagenum%8;
    if((a>>r) & 1)
    {
        a -= 1<<r;
        page_tracker[pagenum/8] = a;
    }
    else
    {

    }
}

void init_page_alloc()
{
    uint64_t maxmem = 0;
    for(int i = 0; i<*memnum; i++)
    {
        maxmem += memmap[i].length;
    }
    max_page = maxmem>>12; //4kb blocks
    uint64_t blocks = max_page >> 3; //
    int diff = max_page - (blocks << 3);
    uint8_t last = 256 - (1<<(8-diff));
    page_tracker[max_page-1] = last;
    //todo : reserve unusable memory using memmap
}

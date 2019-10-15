#include "page_allocator.h"
bool pstatus(int i)
{
    return (page_tracker[i / 8] >> (i % 8)) & 1;
}

extern struct def_vga_screen default_screen;
int palloc()
{
    // putchar(&default_screen, '.');
    preserve(next_available);
    int p = next_available;
    find_next_free();
    return p;
}

void find_next_free()
{
    int p = next_available;
    int i = 0;

    for (i = p + 1;
      (i <= max_page) &&
      pstatus(i);
      i++)
    {
        // putchar(&default_screen, '-');
    }
    next_available = i;
}

void pfree(int pagenum)
{
    int8_t a = page_tracker[pagenum / 8];
    int r    = pagenum % 8;

    if (pstatus(pagenum)) {
        a -= 1 << r;
        page_tracker[pagenum / 8] = a;
    } else   { }
    next_available = pagenum;
}

void preserve(int pagenum)
{
    int8_t a = page_tracker[pagenum / 8];
    int r    = pagenum % 8;

    if (pstatus(pagenum)) { } else {
        a += 1 << r;
        page_tracker[pagenum / 8] = a;
    }
}

void init_page_alloc()
{
    uint64_t maxmem = 0;

    maxmem += memmap[*nummem - 1].base + memmap[*nummem - 1].length;

    max_page = maxmem >> 12;         // 4kb blocks
    uint64_t blocks = max_page >> 3; // number of blocks for the map
    int diff        = max_page - (blocks << 3);
    uint8_t last    = 256 - (1 << (8 - diff));
    page_tracker[max_page - 1] = last;
    putstring(&default_screen, "Reserving unuable memory\n");
    // reserve unusable memory
    for (int i = 0; i < *nummem; i++) {
        if (memmap[i].type != 1) {
            putstring(&default_screen, "Found unusable memory\n");
            uint64_t a = memmap[i].base >> 12;                      // first unavailable page
            uint64_t b = (memmap[i].base + memmap[i].length) >> 12; // last unavailable page
            for (uint64_t j = a; j <= b; j++) {
                preserve(j);
                putstring(&default_screen, ".");
            }
            putstring(&default_screen, "Reserved space\n");
        }
    }
    putstring(&default_screen, "Reserved unuable memory\n");
    for (int i = 0xA0; i < 0x100; i++) {
        preserve(i);
    }
}

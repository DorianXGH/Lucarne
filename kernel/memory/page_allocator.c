#include "page_allocator.h"
bool pstatus(int i) // returns if the page is allocated or not
{
    return (page_tracker[i / 8] >> (i % 8)) & 1;
}

extern struct def_vga_screen default_screen; // for debugging purposes
int palloc()                                 // reserve a single page
{
    preserve(next_available); // reserve the next available page
    int p = next_available;
    find_next_free(); // find a new available page
    return p;         // return the page
}

int palloc_n(int size) // reserves multiple contiguous pages
{
    int k      = next_available; // begin from the first available page
    bool found = false;

    while (!found && k < max_page) {         // for each page while no contiguous pages have been found
        while (pstatus(k) && k < max_page) { // forward while the pages are allocated
            k++;
        }
        int p = k;
        while (!pstatus(p) && (p - k <= size) && p < max_page) { // check if following pages are available
            p++;
        }
        found |= p - k >= size; // if they are : end the search
        if (!found) k = p;      // if the next contiguous pages do not contain the needed space, ignore them
    }
    if (found) {                         // if the space was found
        for (int p = 0; p < size; p++) { // reserve the pages
            preserve(k + p);
        }
    }
    find_next_free(); // find next available page
    return k;
}

void find_next_free() // finds the next available page
{
    int p = next_available; // beginning from the previous next available page
    int i = 0;

    for (i = p + 1;
      (i <= max_page) &&
      pstatus(i); // increment i as long as the page i is not available
      i++)
    { }
    next_available = i; // set i to be the next available page
}

void pfree(int pagenum) // frees the page passed as argument
{
    int8_t a = page_tracker[pagenum / 8]; // find byte in the tracker
    int r    = pagenum % 8;               // find bit in the tracker byte

    if (pstatus(pagenum)) { // unset the allocated bit
        a -= 1 << r;
        page_tracker[pagenum / 8] = a;
    } else   { }
    // TODO : check if the next_available page is before the freed page
    next_available = pagenum; // set it as the next available
}

void preserve(int pagenum) // reserve a page, see above for comments : it behaves the same
{
    int8_t a = page_tracker[pagenum / 8];
    int r    = pagenum % 8;

    if (pstatus(pagenum)) { } else {
        a += 1 << r;
        page_tracker[pagenum / 8] = a;
    }
}

void init_page_alloc() // initialises the allocator
{
    uint64_t maxmem = 0;

    maxmem += memmap[*nummem - 1].base + memmap[*nummem - 1].length; // get the amount of memory present from the last memory segment in the map

    max_page = maxmem >> 12;             // 4kb blocks
    uint64_t blocks = max_page >> 3 + 1; // number of blocks for the map
    for (int k = 0; k < blocks; k++) {
        page_tracker[k] = 0xFF;
    }

    putstring(&default_screen, "Reserving unusable memory\n");
    // reserve unusable memory
    for (int i = 0; i < *nummem; i++) {
        if (memmap[i].type == 1) {
            putstring(&default_screen, "Found usable memory\n");
            uint64_t a = memmap[i].base >> 12 + 1;                  // first available page
            uint64_t b = (memmap[i].base + memmap[i].length) >> 12; // last available page
            for (uint64_t j = a; j <= b; j++) {                     // free the available pages
                pfree(j);
            }
        }
    }
    next_available = 0;
    putstring(&default_screen, "Reserved unuable memory\n");
}

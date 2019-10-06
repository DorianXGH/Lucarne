#include "memory_segment.h"
void
print_map(struct def_vga_screen * s)
{
    for (int i = 0; i < *nummem; i++) {
        char basenum[16];
        char lennum[16];
        prntnum(memmap[i].base, '+', basenum, 16);
        prntnum(memmap[i].length, '+', lennum, 16);
        putstring(s, basenum);
        putchar(s, '|');
        putstring(s, lennum);
        putchar(s, ' ');

        if (memmap[i].type == 0) {
            putstring(s, "not a segment");
        }
        if (memmap[i].type == 1) {
            putstring(s, "usable");
        }
        if (memmap[i].type >= 2) {
            putstring(s, "unusable");
        }
        putchar(s, '\n');
    }
}

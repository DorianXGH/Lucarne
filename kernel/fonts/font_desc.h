#ifndef FONT_DESC_H
#define FONT_DESC_H
#include "../drivers/screen.h"
#include <stdint.h>
#include "../memory/page_allocator.h"
struct font_desc {
    uint8_t * chars[256];
    uint8_t   charmap[256];
    int       charwidth;
    int       charheight;
    int       numchar;
};

void ft_add_char(struct font_desc * ft, uint8_t * sp, uint8_t c);

void ft_print_char(struct def_vga_screen * s, struct font_desc * ft, uint8_t c, int x, int y, uint32_t color);


#endif /* ifndef FONT_DESC_H */

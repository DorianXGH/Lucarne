#include "font_desc.h"
void ft_add_char(struct font_desc * ft, uint8_t * sp, uint8_t c)
{
    ft->chars[ft->numchar] = sp;
    ft->charmap[c]         = ft->numchar;
    ft->numchar++;
}

void ft_print_char(struct def_vga_screen * s, struct font_desc * ft, uint8_t c, int x, int y, uint32_t color)
{
    int p = palloc();
    uint32_t * pixs = (uint32_t *) (p * 0x1000);
    struct sprite spr;

    spr.bpp    = 32;
    spr.height = ft->charheight;
    spr.width  = ft->charwidth;
    uint8_t * alphamap = ft->chars[ft->charmap[c]];
    for (int i = 0; i < spr.height * spr.width; i++) {
        pixs[i] = color | (((uint32_t) alphamap[i]) << 24);
    }
    spr.pixels = (uint8_t *) pixs;
    putsprite(s, &spr, x, y);
    pfree(p);
}

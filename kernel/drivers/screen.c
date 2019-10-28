#include "screen.h"

void putpixel(struct def_vga_screen * s, uint32_t c, int x, int y) // dispatcher function for different video modes set a pixel's color at desired position
// s is a pointer to the abstract screen the pixel will be drawn on, c is the color in RGB, x and y the cartesian coordinates
{
    switch (s->type) {
        case GRAPHIC:
            putpixel_VGA(s, c & 0xFF, x, y);
            break;
        case VESA:
            switch (s->bpp) {
                case 24: { struct color_24 c24;
                           c24.r = (c >> 16) & 0xFF;
                           c24.g = (c >> 8) & 0xFF;
                           c24.b = c & 0xFF;
                           putpixel_24(s, c24, x, y);
                }
                break;
                case 32: { struct color_32 c32;
                           c32.r = (c >> 16) & 0xFF;
                           c32.g = (c >> 8) & 0xFF;
                           c32.b = c & 0xFF;
                           c32.a = 0;
                           putpixel_32(s, c32, x, y);
                }
                break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

inline void putpixel_VGA(struct def_vga_screen * s, char c, int x, int y) // see above, note that it only works on VGA abstract screens, it will do nothing
{ if (s->type == GRAPHIC) s->video_memory[s->width * y + x] = c; }

inline void putpixel_24(struct def_vga_screen * s, struct color_24 c, int x, int y) // see above : only works on VESA 24 bits color, the color is abstracted as
// a struct
{
    if (s->type == VESA && s->bpp == 24) {
        s->video_memory[s->pitch * y + x * 3]     = c.r;
        s->video_memory[s->pitch * y + x * 3 + 1] = c.g;
        s->video_memory[s->pitch * y + x * 3 + 2] = c.b;
    }
}

inline void putpixel_32(struct def_vga_screen * s, struct color_32 c, int x, int y) // see above : only works on VESA 32 bits color
{
    if (s->type == VESA && s->bpp == 32) {
        *((uint32_t *) (s->video_memory + s->pitch * y + x * 4)) = *(uint32_t *) (&c);
    }
}

/*
 * These functions are for text mode
 */

void raw_putchar_wc(struct def_vga_screen * s, char c, char col, int x, int y)
{
    if (s->type == TEXT) {
        if (y < s->height && y >= 0) {
            char * video_memory = s->video_memory;
            int coord = 2 * (s->width * y + x);
            video_memory[coord]     = c;
            video_memory[coord + 1] = col;
        }
    }
}

void raw_putchar(struct def_vga_screen * s, char c, int x, int y)
{
    char greyonblack = 0x07;

    raw_putchar_wc(s, c, greyonblack, x, y);
}

void scrollup(struct def_vga_screen * s, int amount)
{
    if (s->type == TEXT) {
        char * video_memory = s->video_memory;

        for (int i = 0; i < 2 * (s->width * (s->height - amount)); i++) {
            video_memory[i] = video_memory[i + 2 * (s->width * amount)];
        }
        for (int i = 2 * (s->width * (s->height - amount));
          i < 2 * (s->width * (s->height )); i++)
        {
            int a = (i < 0) ? 0 : i;
            video_memory[a] = 0;
        }
        s->cursory -= amount;
        if (s->cursory < 0) {
            s->cursory = 0;
            s->cursorx = 0;
        }
    }
}

void newline(struct def_vga_screen * s)
{
    if (s->type == TEXT) {
        s->cursorx = 0;
        s->cursory++;
        if (s->cursory == s->height) {
            scrollup(s, 1);
        }
    }
}

void remove_char(struct def_vga_screen * s)
{
    if (s->type == TEXT) {
        if (s->cursorx == 0) {
            s->cursorx = s->width - 1;
            if (s->cursory > 0) s->cursory--;
        } else {
            s->cursorx--;
        }
        raw_putchar(s, 0, s->cursorx, s->cursory);
    }
}

void putchar(struct def_vga_screen * s, char c)
{
    if (s->type == TEXT) {
        if (c == '\n') {
            newline(s);
        } else {
            raw_putchar(s, c, s->cursorx, s->cursory);
            if (s->cursorx == s->width - 1) {
                newline(s);
            } else {
                s->cursorx++;
            }
        }
    }
}

void clear(struct def_vga_screen * s)
{
    if (s->type == TEXT) scrollup(s, s->height);
    if (s->type == GRAPHIC) {
        for (int i = 0; i < s->width * s->height; i++) {
            s->video_memory[i] = 0;
        }
    }
}

void putstring(struct def_vga_screen * s, char * str)
{
    int i = 0;

    while (str[i] != 0) {
        putchar(s, str[i]);
        i++;
    }
}

void putsprite(struct def_vga_screen * s, struct sprite * spr, int x0, int y0) // puts a sprite on a screen in the desired location
{
    int bytespp    = (s->bpp / 8);
    int sprbytespp = (spr->bpp / 8);
    int where      = y0 * s->pitch + x0 * bytespp;
    int wherespr   = 0;
    int y = 0;
    int x = 0;

    for (int i = 0; i < (spr->width * spr->height); i++) {
        if (x0 + x < s->width && y0 + y < s->height) {                                                  // stop memory corruption
            if (sprbytespp == 4 && (bytespp == 3 || bytespp == 4) && spr->pixels[wherespr + 3] < 255) { // racalculates pixel as a weighed average
                float alpha = (float) ((int32_t) spr->pixels[wherespr + 3]) / 255.01;
                for (int j = 0; j < 3; j++) {
                    int or  = (uint8_t) s->video_memory[where + j];
                    int nw  = spr->pixels[wherespr + j];
                    float v = (1. - alpha) * or + alpha * nw;
                    s->video_memory[where + j] = (uint8_t) v;
                }
            } else { // if there's no alpha to consider : just copy
                for (int j = 0; j < min(bytespp, sprbytespp); j++) {
                    s->video_memory[where + j] = spr->pixels[wherespr + j];
                }
            }
            x++;
            where    += bytespp;
            wherespr += sprbytespp;
            if (x >= spr->width) {
                x = 0;
                y++;
                where    = (y0 + y) * s->pitch + x0 * bytespp;
                wherespr = y * spr->width * sprbytespp;
            }
        }
    }
} /* putsprite */

void set_screen_alpha(struct def_vga_screen * s, uint8_t a) // sets the screen alpga
{
    if (s->bpp == 32 && s->type == VESA) {
        for (uint32_t i = 3; i < s->height * s->pitch; i += 4) {// on each alpha channel
            s->video_memory[i] = a;
        }
    }
}

void blit(struct def_vga_screen * src, struct def_vga_screen * dest, uint32_t x0, uint32_t y0)
{
    struct sprite spr;

    spr.bpp    = src->bpp;
    spr.width  = src->width;
    spr.height = src->height;
    spr.pixels = src->video_memory;
    putsprite(dest, &spr, x0, y0);
}

void blit_shell(struct def_shell * src, struct def_vga_screen * dest, uint32_t x0, uint32_t y0)
{
    if (src->appointed_screen->type == TEXT && dest->type == VESA) {
        int x = x0;
        int y = y0;
        for (int i = 0; i < src->appointed_screen->height; i++) {
            for (int j = 0; j < src->appointed_screen->width; j++) {
                ft_print_char(dest, src->font, src->appointed_screen->video_memory[2 * (i * src->appointed_screen->width + j)], x, y, src->term_color);
                x += src->font->interchar_x + src->font->charwidth;
            }
            y += src->font->interchar_y + src->font->charheight;
        }
    }
}

#include "screen.h"

void putpixel(struct def_vga_screen * s, char c, int x, int y)
{ if (s->type == GRAPHIC) s->video_memory[s->width * y + x] = c; }

void putpixel_24(struct def_vga_screen * s, struct color_24 c, int x, int y)
{
    if (s->type == VESA && s->bpp == 24) {
        s->video_memory[s->pitch * y + x * 3]     = c.r;
        s->video_memory[s->pitch * y + x * 3 + 1] = c.g;
        s->video_memory[s->pitch * y + x * 3 + 2] = c.b;
    }
}

void putpixel_32(struct def_vga_screen * s, struct color_32 c, int x, int y)
{
    if (s->type == VESA && s->bpp == 32) {
        s->video_memory[s->pitch * y + x * 4]     = c.r;
        s->video_memory[s->pitch * y + x * 4 + 1] = c.g;
        s->video_memory[s->pitch * y + x * 4 + 2] = c.b;
        s->video_memory[s->pitch * y + x * 4 + 3] = c.a;
    }
}

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

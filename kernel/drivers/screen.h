#ifndef SCREEN_H
#define SCREEN_H
#include <stdint.h>
#include "../shell/shell.h"
#include "../util.h"

enum display_type {
    TEXT,
    GRAPHIC,
    VESA
};

struct def_vga_screen {
    int               width;
    int               height;
    int               pitch;
    int               bpp;
    int               cursorx;
    int               cursory;
    enum display_type type;
    char *            video_memory;
};

struct color_24 {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} __attribute__((packed));

struct color_32 {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} __attribute__((packed));

struct sprite {
    uint32_t  bpp;
    uint32_t  width;
    uint32_t  height;
    uint8_t * pixels;
} __attribute__((packed));


struct def_vga_screen default_screen;
void remove_char(struct def_vga_screen * s);
void raw_putchar_wc(struct def_vga_screen * s, char c, char col, int x, int y);

void raw_putchar(struct def_vga_screen * s, char c, int x, int y);

void putpixel_VGA(struct def_vga_screen * s, char c, int x, int y);
void putpixel(struct def_vga_screen * s, uint32_t c, int x, int y);
void putpixel_24(struct def_vga_screen * s, struct color_24 c, int x, int y);
void putpixel_32(struct def_vga_screen * s, struct color_32 c, int x, int y);

void putsprite(struct def_vga_screen * s, struct sprite * spr, int x, int y);

void scrollup(struct def_vga_screen * s, int amount);
void newline(struct def_vga_screen * s);
void putchar(struct def_vga_screen * s, char c);

void clear(struct def_vga_screen * s);

void putstring(struct def_vga_screen * s, char * str);

void blit(struct def_vga_screen * src, struct def_vga_screen * dest, uint32_t x0, uint32_t y0);
void blit_shell(struct def_shell * src, struct def_vga_screen * dest, uint32_t x0, uint32_t y0);
void screencopy(struct def_vga_screen * src, struct def_vga_screen * dest);
void set_screen_alpha(struct def_vga_screen * s, uint8_t a);

#endif /* ifndef SCREEN_H */

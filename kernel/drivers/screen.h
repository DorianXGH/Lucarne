#ifndef SCREEN_H
#define SCREEN_H

struct def_vga_screen {
  int width;
  int height;
  int cursorx;
  int cursory;
};
struct def_vga_screen default_screen;

void raw_putchar_wc(struct def_vga_screen * s, char c, char col, int x, int y);

void raw_putchar(struct def_vga_screen * s, char c, int x, int y);

void scrollup(struct def_vga_screen * s, int amount);
void newline(struct def_vga_screen *s);
void putchar(struct def_vga_screen * s, char c);

void clear(struct def_vga_screen * s);

void putstring(struct def_vga_screen * s, char * str);

#endif

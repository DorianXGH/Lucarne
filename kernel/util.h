#ifndef UTIL_H
#define UTIL_H
#include <stdint.h>
#include <stdbool.h>
#include "cpuid/cpuid.h"
#include "drivers/screen.h"

extern struct def_vga_screen default_screen;

void memcpy(char * source, char * dest, int nbytes);
void memcpy2(char * src, char * dest, int n);
void memset(char * dest, char val, int len);
void int_to_ascii(int n, char str[]);
void prntnum(uint64_t n, char sign, char * outbuf, int size);
uint16_t low_16(uint32_t a);
uint16_t high_16(uint32_t a);
bool strcompare(char * a, char * b);
int min(int a, int b);
void print_hex(struct def_vga_screen * s, char * a);
#endif /* ifndef UTIL_H */

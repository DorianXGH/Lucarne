#ifndef UTIL_H
#define UTIL_H
#include <stdint.h>
#include <stdbool.h>

void memcpy(char * source, char * dest, int nbytes);
void memset(char * dest, char val, int len);
void int_to_ascii(int n, char str[]);
void prntnum(uint64_t n, char sign, char * outbuf, int size);
uint16_t low_16(uint32_t a);
uint16_t high_16(uint32_t a);
bool strcompare(char * a, char * b);
int min(int a, int b);
#endif /* ifndef UTIL_H */

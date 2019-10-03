#ifndef UTIL_H
#define UTIL_H
#include <stdint.h>

void memory_copy(char *source, char *dest, int nbytes);
void memory_set(char *dest, char val, int len);
void int_to_ascii(int n, char str[]);
void prntnum(uint64_t n, char sign, char *outbuf, int size);
short int low_16(int a);
short int high_16(int a);
#endif

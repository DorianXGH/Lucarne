#include "util.h"
// these functions are pretty much self explanatory

int min(int a, int b)
{
    return (a < b) ? a : b;
}

bool strcompare(char * a, char * b)
{
    bool eq = true;
    int i   = 0;

    while (a[i] != 0 && b[i] != 0) {
        eq &= a[i] == b[i];
        i++;
    }
    eq &= a[i] == b[i];
    return eq;
}

void memcpy(char * source, char * dest, int nbytes)
{
    int i;

    for (i = 0; i < nbytes; i++) {
        *(dest + i) = *(source + i);
    }
}

void memcpy2(char * src, char * dest, int n)
{
    uint32_t num_dwords = n / 4;
    uint32_t num_bytes  = n % 4;
    uint32_t * dest32   = (uint32_t *) dest;
    uint32_t * src32    = (uint32_t *) src;
    uint8_t * dest8     = ((uint8_t *) dest) + num_dwords * 4;
    uint8_t * src8      = ((uint8_t *) src) + num_dwords * 4;
    uint32_t i;

    for (i = 0; i < num_dwords; i++) {
        dest32[i] = src32[i];
    }
    for (i = 0; i < num_bytes; i++) {
        dest8[i] = src8[i];
    }
}

void memset(char * dest, char val, int len)
{
    char * temp = (char *) dest;

    for (; len != 0; len--) *temp++ = val;
}

/**
 * K&R implementation
 */
void int_to_ascii(int n, char str[])
{
    int i, sign;

    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    /* TODO: implement "reverse" */
}

uint16_t low_16(uint32_t a)
{
    return (uint16_t) a;
}

uint16_t high_16(uint32_t a)
{
    return (uint16_t) (a >> 16);
}

void prntnum(uint64_t n, char sign, char * outbuf, int size)
{
    int i = 12;
    int j = 0;

    do {
        outbuf[i % size] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"[n % 16];
        i--;
        n = n >> 4;
    } while (n > 0);

    if (sign != ' ') {
        outbuf[0 % size] = sign;
        ++j;
    }

    while (++i < 13) {
        outbuf[(j++) % size] = outbuf[i % size];
    }

    outbuf[j % size] = 0;
}

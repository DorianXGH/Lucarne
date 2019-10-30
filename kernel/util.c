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
    uint32_t ecx;
    uint32_t edx;
    bool not_advanced_enough = false;

    cpuid_get_features(&ecx, &edx);

    putpixel(&default_screen, 0xFF0000, 200, 10);


    if (edx & CPUID_FEAT_EDX_SSE) {
        int i;
        putpixel(&default_screen, 0xFFFFFF, 205, 10);
        putpixel(&default_screen, 0xFFFFFF, 206, 10);
        putpixel(&default_screen, 0xFFFFFF, 205, 11);
        putpixel(&default_screen, 0xFFFFFF, 206, 11);
        for (i = 0; i < n / 16; i++) {
            __asm__ __volatile__ ("movups (%0), %%xmm0\n" "movntdq %%xmm0, (%1)\n" : : "r" (src), "r" (dest) : "memory");

            src  += 16;
            dest += 16;
        }
    } else if (n & 15 && edx & CPUID_FEAT_EDX_MMX) {
        n = n & 15;
        int i;
        for (i = 0; i < n / 8; i++) {
            __asm__ __volatile__ ("movq (%0), %%mm0\n" "movq %%mm0, (%1)\n" : : "r" (src), "r" (dest) : "memory");
            src  += 8;
            dest += 8;
        }
        putpixel(&default_screen, 0xFF0000, 210, 10);
    } else {
        not_advanced_enough = true;

        memcpy(src, dest, n);
        putpixel(&default_screen, 0xFFFFFF, 215, 10);
        putpixel(&default_screen, 0xFFFFFF, 215, 11);
    }
    if (n & 7 && !not_advanced_enough) {
        n = n & 7;

        int d0, d1, d2;
        __asm__ __volatile__ (
            "rep ; movsl\n\t"
            "testb $2,%b4\n\t"
            "je 1f\n\t"
            "movsw\n"
            "1:\ttestb $1,%b4\n\t"
            "je 2f\n\t"
            "movsb\n"
            "2:"
            : "=&c" (d0), "=&D" (d1), "=&S" (d2)
            : "0" (n / 4), "q" (n), "1" ((long) dest), "2" ((long) src)
            : "memory");
        putpixel(&default_screen, 0xFF0000, 220, 10);
    }
} /* memcpy2 */

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

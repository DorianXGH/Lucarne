#include "util.h"

void memory_copy(char *source, char *dest, int nbytes) {
    int i;
    for (i = 0; i < nbytes; i++) {
        *(dest + i) = *(source + i);
    }
}

void memory_set(char *dest, char val, int len) {
    char *temp = (char *)dest;
    for ( ; len != 0; len--) *temp++ = val;
}

/**
 * K&R implementation
 */
void int_to_ascii(int n, char str[]) {
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

short int low_16(int a) {
    return (short int)a;
}
short int high_16(int a)
{
    return (short int)(a>>16);
}

void prntnum(unsigned long n, int base, char sign, char *outbuf, int size)
{

    int i = 12;
    int j = 0;

    do{
        outbuf[i%size] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"[n % base];
        i--;
        n = n/base;
    }while( n > 0);

    if(sign != ' '){
        outbuf[0%size] = sign;
        ++j;
    }

    while( ++i < 13){
       outbuf[(j++)%size] = outbuf[i%size];
    }

    outbuf[j%size] = 0;

}

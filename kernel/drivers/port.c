#include "port.h"

/**
 * Read a byte from the specified port
 */
unsigned char port_byte_in(short int port)
{
    char result;

    /* Inline assembler syntax
     * !! Notice how the source and destination registers are switched from NASM !!
     *
     * '"=a" (result)'; set '=' the C variable '(result)' to the value of register e'a'x
     * '"d" (port)': map the C variable '(port)' into e'd'x register
     *
     * Inputs and outputs are separated by colons
     */
    __asm__ ("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void port_byte_out(short int port, char data)
{
    /* Notice how here both registers are mapped to C variables and
     * nothing is returned, thus, no equals '=' in the asm syntax
     * However we see a comma since there are two variables in the input area
     * and none in the 'return' area
     */
    __asm__ __volatile__ ("out %%al, %%dx" : : "a" (data), "d" (port));
}

unsigned short int port_word_in(short int port)
{
    short int result;

    __asm__ ("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}

void port_word_out(short int port, short int data)
{
    __asm__ __volatile__ ("out %%ax, %%dx" : : "a" (data), "d" (port));
}

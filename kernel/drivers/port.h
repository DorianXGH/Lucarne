#ifndef PORT_H
#define PORT_H
#include <stdint.h>

uint8_t port_byte_in(uint16_t port);
void port_byte_out(uint16_t port, uint8_t data);
uint16_t port_word_in(uint16_t port);
void port_word_out(uint16_t port, uint16_t data);

uint8_t inb(uint16_t port);

void outb(uint16_t port, uint8_t data);

uint16_t inw(uint16_t port);

void outw(uint16_t port, uint16_t data);

#endif // ifndef PORT_H

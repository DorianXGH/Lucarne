#ifndef PORT_H
#define PORT_H

unsigned char port_byte_in(short int port);
void port_byte_out(short int port, char data);
unsigned short port_word_in(short int port);
void port_word_out(short int port, short int data);

#endif

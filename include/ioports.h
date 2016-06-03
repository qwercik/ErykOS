#ifndef IOPORTS_H
#define IOPORTS_H

/*
Later, there will be #define with ports
*/

#include <types.h>

void outportb(uint16_t port, uint8_t data);
uint8_t inportb(uint16_t port);

#endif
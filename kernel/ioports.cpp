#include <ioports.h>

void outportb(uint16_t port, uint8_t data)
{
	__asm__ __volatile__ ("outb %1, %0" : : "dN" (port), "a" (data));
}

uint8_t inportb(uint16_t port)
{
	uint8_t data;
	__asm__ __volatile__ ("inb %1, %0" : "=a" (data) : "dN" (port));
	return data;
}
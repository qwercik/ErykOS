#include <Screen.h>
#include <types.h>

int main (void* multibootInfoStructure, uint32_t multibootMagicNumber)
{
	Screen scr;
	scr.clearScreen();

	if (multibootMagicNumber != 0x2BADB002)
	{
		scr.setFontColor(Screen::RED);
		scr.printString("Something went wrong. System will be halted");
		asm("hlt");
	}
	
	scr.printString("Welcome to ErykOS!");
	return 0;
}
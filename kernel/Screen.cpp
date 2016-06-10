#include <Screen.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ioports.h>

Screen::Screen(Color fontColor, Color backgroundColor) :screenHeight(25), screenWidth(80)
{
	this -> fontColor = fontColor;
	this -> backgroundColor = backgroundColor;

	videoMemory = (int16_t*) 0xB8000;

	currentPositionX = 0;
	currentPositionY = 0;

	isCursorEnabled = true;
}

void Screen::printChar(uint8_t character)
{
	switch (character)
	{
		case '\n':
			currentPositionX = 0;
			if (currentPositionY == screenHeight - 1)
				scrollScreen();
			else
				currentPositionY++;
			break;

		case '\r':
			currentPositionX = 0;
			break;

		case '\b':
			if (currentPositionX > 0)
			{
				currentPositionX--;
				moveCursorXY(currentPositionX, currentPositionY);
			}
			break;
		default:
			uint16_t resultCursorPosition = currentPositionY * screenWidth + currentPositionX;
			uint16_t videoData = ((fontColor | backgroundColor << 4) << 8) | character;

			*(videoMemory + resultCursorPosition) = videoData;

			if (currentPositionX + 1 == screenWidth)
			{
				currentPositionX = 0;
				currentPositionY++;

				if (currentPositionY == screenHeight - 1)
					scrollScreen();
				
			}
			else
				currentPositionX++;
		}
	
	if (isCursorEnabled)
		updateCursor();

}

void Screen::printString(string stringToPrint, ...)
{
	int i = 0;
	char buffer[9];
	va_list argumentsToPrint;
	va_start(argumentsToPrint, stringToPrint);

	while (stringToPrint[i] != '\0')
	{	
		switch (stringToPrint[i])
		{
			case '%':
				switch (stringToPrint[i + 1])
				{
					case 'd':
						printString(itoa(va_arg(argumentsToPrint, int), buffer, 10));
						break;
					case 's':
						printString(va_arg(argumentsToPrint, string));
						break;
				}
				i++;
			break;

			default:
				printChar(stringToPrint[i]);

		}

		i++;
	}
}

void Screen::clearLine(uint8_t lineNumber)
{
	currentPositionX = 0;

	uint16_t videoData = 0x20 | ((fontColor | backgroundColor << 4) << 8);
	uint16_t linePosition = screenWidth * lineNumber;

	for (int i = 0; i < screenWidth; i++)
		*(videoMemory + linePosition + i) = videoData;
}

void Screen::clearScreen()
{
	currentPositionX = 0;
	currentPositionY = 0;

	updateCursor();

	uint16_t videoData = 0x20 | ((fontColor | backgroundColor << 4) << 8); //try later to change this

	for (int i = 0; i < screenHeight * screenWidth; i++)
		*(videoMemory + i) = videoData;
}

void Screen::setColor(Color fontColor, Color backgroundColor)
{
	this -> fontColor = fontColor;
	this -> backgroundColor = backgroundColor;
}

void Screen::setFontColor(Color fontColor)
{
	this -> fontColor = fontColor;
}

void Screen::setBackgroundColor(Color backgroundColor)
{
	this -> backgroundColor = backgroundColor;
}

void Screen::updateCursor()
{
	uint16_t cursorPosition = currentPositionY * screenWidth + currentPositionX;

	outportb(0x3D4, 14); //Setting to send high byte of 16bit cursorposition variable
	outportb(0x3D5, (cursorPosition >> 8) & 0xFF); //Sending high byte
	outportb(0x3D4, 15); //Setting to send low byte
	outportb(0x3D5, cursorPosition & 0xFF); //Sending low byte of 16bit cursorposition variable
}

void Screen::scrollScreen()
{
	for (int i = 0; i < (screenHeight - 1) * screenWidth * 2; i++)
		*(videoMemory + i) = *(videoMemory + i + screenWidth);

	currentPositionY = screenHeight - 1;

	updateCursor();
}

void Screen::hideCursor()
{
	isCursorEnabled = false;

	uint16_t cursorPosition = screenHeight * screenWidth + 1;

	outportb(0x3D4, 14); //Setting to send high byte of 16bit cursorposition variable
	outportb(0x3D5, (cursorPosition >> 8) & 0xFF); //Sending high byte
	outportb(0x3D4, 15); //Setting to send low byte
	outportb(0x3D5, cursorPosition & 0xFF); //Sending low byte of 16bit cursorposition variable
}

void Screen::showCursor()
{
	isCursorEnabled = true;

	uint16_t cursorPosition = currentPositionY * screenWidth + currentPositionX;

	outportb(0x3D4, 14); //Setting to send high byte of 16bit cursorposition variable
	outportb(0x3D5, (cursorPosition >> 8) & 0xFF); //Sending high byte
	outportb(0x3D4, 15); //Setting to send low byte
	outportb(0x3D5, cursorPosition & 0xFF); //Sending low byte of 16bit cursorposition variable
}

void Screen::moveCursorXY(uint8_t positionX, uint8_t positionY)
{
	currentPositionX = positionX;
	currentPositionY = positionY;

	if (isCursorEnabled)
		updateCursor();
}
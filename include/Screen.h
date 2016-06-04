#ifndef SCREEN_H
#define SCREEN_H

#include <types.h>

class Screen
{

public:

	enum Color
	{
		BLACK,
		BLUE,
		GREEN,
		AQUA,
		RED,
		PURPLE,
		ORANGE,
		WHITE,
		GRAY,
		LIGHT_BLUE,
		LIGHT_GREEN,
		CYAN,
		LIGHT_RED,
		PINK,
		YELLOW,
		BRIGHT_WHITE
	};

	
	Screen(Color fontColor = WHITE, Color backgroundColor = BLACK);

	void printChar(uint8_t character);
	void printString(string stringToPrint);

	void clearScreen();
	void clearLine(uint8_t lineNumber);

	void setColor(Color fontColor, Color backgroundColor);
	void setFontColor(Color fontColor);
	void setBackgroundColor(Color backgroundColor);

	void hideCursor();
	void showCursor();
	//void moveCursorXY(uint8_t positionX, uint8_t positionY); //not developed yet
private:

	bool isCursorEnabled;
	
	const uint8_t screenHeight;
	const uint8_t screenWidth;

	int16_t* videoMemory;

	Color fontColor, backgroundColor;

	uint8_t currentPositionX, currentPositionY;
	
	
	void updateCursor(); //It updates the underline character ('_') 
	void scrollScreen();

};

#endif
#pragma once
#include <Windows.h>
#include <conio.h>
#include <iostream>
#include "Player.h"

#define CONSOLE_WIDTH 1000
#define CONSOLE_HEIGHT 800

#define CONSOLE_TITLE L"Hangman - the game"
#define CONSOLE_BACKGROUND_COLOR "Color F0"

#define SET_TEXT_RED() SetConsoleTextAttribute(consoleHandle, 12 | BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
#define SET_TEXT_BLUE() SetConsoleTextAttribute(consoleHandle, 1 | BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);


class IWindow {
public:
	IWindow(const size_t width = CONSOLE_WIDTH, const size_t height = CONSOLE_HEIGHT) :
		consoleHandle{ setConsoleWindow(width, height)},
		innerField{}
	{};
	virtual void draw() const = 0;
	virtual ~IWindow() = default;
protected:
	struct InnerField {
		InnerField() {
			CONSOLE_SCREEN_BUFFER_INFO consoleBuffer;
			HANDLE consoleHandle{ GetStdHandle(STD_OUTPUT_HANDLE) };

			GetConsoleScreenBufferInfo(consoleHandle, &consoleBuffer);

			noOfRows = consoleBuffer.srWindow.Bottom - consoleBuffer.srWindow.Top;
			noOfCols = consoleBuffer.srWindow.Right - consoleBuffer.srWindow.Left - 1;
		}
		size_t noOfRows;
		size_t noOfCols;
	};
	HANDLE consoleHandle;
	InnerField innerField;
	void setCoursorToXY(const size_t xCoord, const size_t yCoord) const;
	HANDLE setConsoleWindow(const size_t width, const size_t height) const;
};


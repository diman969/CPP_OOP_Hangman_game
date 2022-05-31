#include "IWindow.h"



HANDLE IWindow::setConsoleWindow(const size_t width, const size_t height) const
{
	SetConsoleTitle(CONSOLE_TITLE);
	system(CONSOLE_BACKGROUND_COLOR);

	HANDLE consoleHandle{ GetStdHandle(STD_OUTPUT_HANDLE) };
	HWND console = GetConsoleWindow();
	CONSOLE_SCREEN_BUFFER_INFO consoleBuffer;
	RECT consoleCoords{ 150, 150, height, width };

	_SMALL_RECT consolePosition;
	consolePosition.Top = 0;
	consolePosition.Left = 0;
	consolePosition.Bottom = height - 1;
	consolePosition.Right = width - 1;

	MoveWindow(console, consoleCoords.left, consoleCoords.top, width, height, FALSE);

	GetConsoleScreenBufferInfo(consoleHandle, &consoleBuffer);

	COORD coord;
	coord.X = consoleBuffer.srWindow.Right - consoleBuffer.srWindow.Left + 1;
	coord.Y = consoleBuffer.srWindow.Bottom - consoleBuffer.srWindow.Top + 1;


	CONSOLE_CURSOR_INFO coursor;
	coursor.dwSize = 16;
	coursor.bVisible = FALSE;

	SetConsoleScreenBufferSize(consoleHandle, coord);
	SetConsoleCursorInfo(consoleHandle, &coursor);
	SetConsoleWindowInfo(consoleHandle, TRUE, &consolePosition);

	SetWindowLong(console, GWL_STYLE, GetWindowLong(console, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
	return consoleHandle;
}
void IWindow::setCoursorToXY(size_t xCoord, size_t yCoord) const{
	COORD position;
	position.X = xCoord;
	position.Y = yCoord;
	SetConsoleCursorPosition(consoleHandle, position);
}


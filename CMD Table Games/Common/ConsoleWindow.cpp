#include <iostream>
#include <algorithm>
#include <exception>
#include "ConsoleWindow.h";

ConsoleWindow::ConsoleWindow(int width, int height, const std::wstring& title)
: width_(width), height_(height), title_(title),
hInput_(GetStdHandle(STD_INPUT_HANDLE)), hOutput_(GetStdHandle(STD_OUTPUT_HANDLE)), hWnd_(GetConsoleWindow()) {

	if (hWnd_ == NULL || hInput_ == INVALID_HANDLE_VALUE || hOutput_ == INVALID_HANDLE_VALUE)
	{
		throw std::runtime_error("Критическая ошибка: Не удалось найти окно консоли!\n");
	}

	if(!isValidSize(width_, height_))
	{
		std::cerr << "Неверное значение для размеров окна!\nЗначения возвращены к стандартным\n";
		width_ = 100;
		height_ = 60;
	}

	SetConsoleTitleW(title_.c_str());

	changingConsoleProperties();
}

bool ConsoleWindow::isValidSize(int width, int height) {
	if (width <= 0 || height <= 0) return false;

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	CONSOLE_FONT_INFOEX fontInfo;
	fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	if (!GetCurrentConsoleFontEx(hOutput_, FALSE, &fontInfo))
	{
		throw std::runtime_error("Критическая ошибка: Не удалось узнать шрифт консоли!\n");
	}
	int fontWidth = fontInfo.dwFontSize.X;
	int fontHeight = fontInfo.dwFontSize.Y;

	if (fontWidth == 0 || fontHeight == 0) return false;
	
	int maxWidth = screenWidth / fontWidth;
	int maxHeight = screenHeight / fontHeight;

	return (width <= maxWidth && height <= maxHeight);
}

void ConsoleWindow::changingConsoleProperties() {
	LONG style = GetWindowLong(hWnd_, GWL_STYLE);
	style &= ~WS_THICKFRAME; // Отключает изменение размера окна
	style &= ~WS_MAXIMIZEBOX; // Отключает кнопку разворачивания окна
	SetWindowLong(hWnd_, GWL_STYLE, style);
	SetWindowPos(hWnd_, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

	SMALL_RECT tmpSize = { 0, 0, 1, 1 };
	SetConsoleWindowInfo(hOutput_, TRUE, &tmpSize);

	COORD bufferSize = { static_cast<SHORT>(width_), static_cast<SHORT>(height_) };
	SetConsoleScreenBufferSize(hOutput_, bufferSize);

	SMALL_RECT windowSize = { 0, 0, static_cast<SHORT>(width_ - 1), static_cast<SHORT>(height_ - 1) };
	SetConsoleWindowInfo(hOutput_, TRUE, &windowSize); // Изменяет размер окна

	DWORD mode;
	GetConsoleMode(hInput_, &mode);
	mode &= ~ENABLE_QUICK_EDIT_MODE; // Отключает выделение
	mode |= ENABLE_MOUSE_INPUT; // Включает отслеживание мыши
	SetConsoleMode(hInput_, mode);
}

void ConsoleWindow::clearScreen() {
	COORD coordScreen = { 0, 0 };
	DWORD cCharsWritten;
	DWORD dwConSize;
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (!GetConsoleScreenBufferInfo(hOutput_, &csbi)) return;
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	FillConsoleOutputCharacter(hOutput_, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten);
	SetConsoleCursorPosition(hOutput_, coordScreen);
}
#pragma once

#include <Windows.h>
#include <string>
#include <exception>

class ConsoleWindow {
private:
	HANDLE hInput_;
	HANDLE hOutput_;
	HWND hWnd_;
	int width_{};
	int height_{};
	std::wstring title_;
public:
	// Размер консольного окна указывается в количестве символов консоли
	ConsoleWindow(int width = 100, int height = 60, const std::wstring& title = L"Консольное окно");

	bool isValidSize(int width, int height);

	void changingConsoleProperties();

	void clearScreen();

	int getConsoleWidth() { return width_; }
	int getConsoleHeight() { return height_; }
};
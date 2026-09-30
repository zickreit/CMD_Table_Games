#pragma once

#include <Windows.h>
#include <string>
#include <exception>

class ConsoleWindow {
protected:
	HANDLE hInput_;
	HANDLE hOutput_ = GetStdHandle(STD_OUTPUT_HANDLE);
	HWND hWnd_;
	int width_{};
	int height_{};
	std::wstring title_;
public:
	ConsoleWindow(int width = 100, int height = 60, const std::wstring& title = L"Консольное окно");

	bool isValidSize(int width, int height);

	void changingConsoleProperties();

	void clearScreen();
};
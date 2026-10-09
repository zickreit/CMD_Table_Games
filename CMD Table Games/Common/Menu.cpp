#include <iostream>
#include <Windows.h>
#include "Headers/Menu.h"
#include "Headers/ConsoleWindow.h"

MenuUI::MenuUI() 
	: ConsoleWindow::ConsoleWindow(70, 50, L"Меню") {
	buttons_.push_back(Button("Крестики-Нолики"));
	buttons_.push_back(Button("Шашки"));
	buttons_.push_back(Button("Шахматы"));
	buttons_.push_back(Button("Выход"));
}

void MenuUI::drawMenu() {
	for (auto button : buttons_)
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(getHandleOutput(), &csbi);
		std::cout << button.drawButton(csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y) << '\n';
	}
}

void drawMenu() {
	MenuUI mui;
	mui.drawMenu();
}
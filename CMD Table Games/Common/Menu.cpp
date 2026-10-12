#include <iostream>
#include <Windows.h>
#include "Headers/Menu.h"
#include "Headers/Button.h"
#include "Headers/ConsoleWindow.h"

MenuUI::MenuUI() {
	buttons_.push_back(Button("Крестики-Нолики"));
	buttons_.push_back(Button("Шашки"));
	buttons_.push_back(Button("Шахматы"));
	buttons_.push_back(Button("Выход"));
}

std::vector<Button>& MenuUI::drawMenu(ConsoleWindow& cw) {
	HANDLE hOutput = cw.getHandleOutput();
	for (auto& button : buttons_)
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(hOutput, &csbi);
		std::cout << button.drawButton(csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y) << '\n';
	}
	return buttons_;
}
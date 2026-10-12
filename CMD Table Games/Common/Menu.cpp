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
	std::cout << std::string((cw.getConsoleWidth() - 61) / 2, ' ') << "█ █ ▄▀█ █▀▀ ▀█▀ █▀█  █▀█ █▄▄ █ █ █▄▄ █ █▀▀  █ ▄█ █▀▀ █▀█ █▄▄ █" << '\n';
	std::cout << std::string((cw.getConsoleWidth() - 61) / 2, ' ') << "█▀█ █▀█ █▄▄  █  █▄█ ▄█ █ █▄█ █▀█ █▄█ █ ██▄  █▀ █ █   █▀▀ █▄█ █" << '\n' << '\n';
	for (auto& button : buttons_)
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(hOutput, &csbi);
		std::cout << button.drawButton(csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y) << "            ";
	}
	return buttons_;
}

int MenuUI::getPressedButtonId(ConsoleWindow& cw) {
	for (int i{}; i < buttons_.size(); ++i)
	{
		buttons_.at(i).setDrawedState(false);
		if (buttons_.at(i).getState() == Button::State::pressed)
		{
			return i;
		}
	}
}

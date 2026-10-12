// CMD Table Game - это проект об различных классических настольных играх, реализованных в консоли
// Список доступных игр:
//	1. Крестики-нолики ...
//	2. Шашки -
//	3. Шахматы -

#include <iostream>

#if defined(_WIN32) && !defined(__CYGWIN__)
#include <vector>
#include <Windows.h>
#include "TicTacToe/Headers/TicTacToeGame.h"
#include "Common/Headers/ConsoleWindow.h"
#include "Common/Headers/Menu.h"
#include "Common/Headers/MenuInteraction.h"

int main(int argc, char* argv[]) {
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	while (1)
	{
		ConsoleWindow cw(70, 20, L"Настольные игры в консоли");
		std::cout << "\033[?25l\n";
		MenuUI menu;
		MenuInteraction mi;
		bool rebootRequired{};

		while (!rebootRequired)
		{
			cw.setCursorPos(0, 0);
			auto& buttons = menu.drawMenu(cw);
			bool isButtonPressed = mi.mouseEventWaiting(cw, buttons);
			if (!isButtonPressed) continue;
			int pressedButtonId = menu.getPressedButtonId(cw);
			switch (pressedButtonId)
			{
			case 0:
				ticTacToe();
				rebootRequired = true;
				break;
			case 1:
				rebootRequired = true;
				break;
			case 2:
				rebootRequired = true;
				break;
			case 3:
				exit(1);
				break;
			default:
				std::cerr << "Произошла ошибка: нажата неизвестная кнопка!\n";
				exit(-1);
			}
		}
	}
}
#else
#include <cstdlib>
	
int main(int argc, char* argv[]) {
	std::cerr << "Error: Code only works on the Windows operating system!\n";
	exit(-1);
}
#endif
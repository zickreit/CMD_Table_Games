// CMD Table Game - это проект об различных классических настольных играх, реализованных в консоли
// Список доступных игр:
//	1. Крестики-нолики ...
//	2. Шашки -
//	3. Шахматы -

#include <iostream>

#if defined(_WIN32) && !defined(__CYGWIN__)
#include <Windows.h>
#include "TicTacToe/Headers/TicTacToeGame.h"
#include "Common/Headers/ConsoleWindow.h"
#include "Common/Headers/Menu.h"
#include "Common/Headers/MenuInteraction.h"

int main(int argc, char* argv[]) {
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	ConsoleWindow cw(70, 50, L"Меню");
	std::cout << "\033[?25l\n";

	while (true)
	{
		cw.setCursorPos(0, 0);
		MenuUI menu;
		MenuInteraction mi;
		
		mi.mouseEventWaiting(cw, menu.drawMenu(cw));
	}
}
#else
#include <cstdlib>
	
int main(int argc, char* argv[]) {
	std::cerr << "Error: Code only works on the Windows operating system!\n";
	exit(-1);
}
#endif
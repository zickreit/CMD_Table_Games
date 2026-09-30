// TicTacToe - игра крестики-нолики.
// Цели реализации игры:
//  - интерфейс игры
//     * большое название игры							| +
//     * игровая сетка									|
//	   * счёт и раунд									|
//     * чей ход										|
//	   * кнопка выхода в меню							|
//	   * кнопка выбора сложности						|
//	- функциональная игровая сетка						|
//	   * хранить информацию об статусе каждой ячейки	| +-
//     * хранить информацию об координатах ячеек		| +-
//	   * взаимодействие через нажатие мышки				|
//  - выбор соперника									|
//	   * соперник второй игрок							|
//	   * соперник бот									|
//       ~ лёгкая сложность (рандом)					|
//	     ~ средняя сложность (50% алгоритм, 50% рандом) |
//       ~ высокая сложная (95% - алгоритм)				|
//

#include <iostream>
#include <thread>
#include <chrono>
#include "TicTacToeGame.h"
#include "Common/ConsoleWindow.h"

TicTacToe::TicTacToe(int gameGridSize)
	: ConsoleWindow::ConsoleWindow(65, 40, L"Крестики-Нолики") {
	gameGridSize_ = gameGridSize;
}

void TicTacToe::startRound() {
	static std::string hideCursor = "\033[?25l\n";
	std::cout << hideCursor;
	for (;;)
	{
		clearScreen();
		drawInterface();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

void TicTacToe::drawInterface() {
	std::cout << "█▄▀ █▀█ █▀▀ █▀▀ ▀█▀ █ ▄█ █▄▀ █ ▄█  ▄▄  █ █ █▀█  █▀█ █ ▄█ █▄▀ █ ▄█" << '\n';
	std::cout << "█ █ █▀▀ ██▄ █▄▄  █  █▀ █ █ █ █▀ █      █▀█ █▄█ ▄█ █ █▀ █ █ █ █▀ █" << '\n';
}

void ticTacToe() {
	TicTacToe game;
	game.startRound();
}
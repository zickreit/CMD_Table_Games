// TicTacToe - игра крестики-нолики.
// Задачи для реализации игры:
//  - интерфейс игры
//     * большое название игры							| +
//     * игровая сетка									| +
//	   * счёт и раунд									|
//     * чей ход										|
//	   * кнопка выхода в меню							|
//	   * кнопка выбора сложности						|
//	   * кнопка изменения размера поля					|
//	- функциональная игровая сетка						|
//	   * хранить информацию об статусе каждой ячейки	| +
//     * хранить информацию об координатах ячеек		| +
//	   * взаимодействие через нажатие мышки				| +-
//  - выбор соперника									|
//	   * соперник второй игрок							|
//	   * соперник бот									|
//       ~ лёгкая сложность (рандом)					|
//	     ~ средняя сложность (50% алгоритм, 50% рандом) |
//       ~ высокая сложная (95% - алгоритм)				|
//

#include <iostream>
#include <algorithm>
#include <string>
#include <exception>
#include "Headers/TicTacToeGame.h"
#include "Common/ConsoleWindow.h"

TicTacToe::TicTacToe(int gameGridSize)
	: ConsoleWindow::ConsoleWindow(65, 40, L"Крестики-Нолики") {
	gridSize_ = std::clamp(gameGridSize, 3, getConsoleWidth() / 4);
	gameGridCoords_.assign((size_t)(gridSize_ * gridSize_), {0, 0, 0, 0});
	gameGridStats_.assign((size_t)(gridSize_ * gridSize_), CellStatus(CellStatus::empty));
	gridSizeWidthMultiplier_ = (getConsoleWidth() - gridSize_) / gridSize_;
	gridSizeWidthMultiplier_ -= gridSizeWidthMultiplier_ % 2 != 0 ? 1 : 0;
	//gridSizeHeightMultiplier_ = (getConsoleHeight() - 10) / gridSize_;
	gridSizeHeightMultiplier_ = gridSizeWidthMultiplier_ / 2;
	while (gridSize_ * gridSizeHeightMultiplier_ + (gridSize_ - 1) > getConsoleHeight())
	{
		--gridSizeHeightMultiplier_;
		gridSizeWidthMultiplier_ -= 2;
	}
}

void TicTacToe::startRound() {
	static std::string hideCursor = "\033[?25l\n";
	std::cout << hideCursor;
	stepCount_ = 1;
	for (;;)
	{
		clearScreen();
		//system("cls");
		gameUI.drawUI(*this);
		mouseInter.mouseEventWaiting(*this);
	}
}

int TicTacToe::getCell(SHORT x, SHORT y) {
	for (int i{}; i < gameGridCoords_.size(); ++i)
	{
		if (x >= gameGridCoords_.at(i).Left && y >= gameGridCoords_.at(i).Top && x <= gameGridCoords_.at(i).Right && y <= gameGridCoords_.at(i).Bottom)
		{
			return i;
		}
	}
	return -1;
}

TicTacToe::CellStatus TicTacToe::getCellStatus(int id) {
	if (id < 0 || id >= gameGridStats_.size())
	{
		throw std::runtime_error("Критическая ошибка: Неверный ID в вызове getCellStatus!\n");
	}
	return gameGridStats_.at(id); 
}


void TicTacToe::setCell(CellStatus cs, int id) {
	if (id < 0 || id >= gameGridStats_.size()) return;
	gameGridStats_.at(id) = cs;
}


void ticTacToe() {
	TicTacToe game(3);
	game.startRound();
}
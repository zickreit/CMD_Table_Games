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
#include <algorithm>
#include <cmath>
#include <string>
#include <sstream>
#include "TicTacToeGame.h"
#include "Common/ConsoleWindow.h"

TicTacToe::TicTacToe(int gameGridSize)
	: ConsoleWindow::ConsoleWindow(65, 40, L"Крестики-Нолики") {
	gridSize_ = std::clamp(gameGridSize, 3, 10);
	gameGridCoords_.assign((size_t)std::pow(gridSize_, gridSize_), {0, 0});
	gameGridStats_.assign((size_t)std::pow(gridSize_, gridSize_), CellStatus(CellStatus::empty));
	gridSizeWidthMultiplier_ = (getConsoleWidth() - gridSize_) / gridSize_;
	gridSizeHeightMultiplier_ = (getConsoleHeight() - 10) / gridSize_;
}

void TicTacToe::startRound() {
	static std::string hideCursor = "\033[?25l\n";
	std::cout << hideCursor;
	for (;;)
	{
		//clearScreen();
		system("cls");
		drawUI();
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	}
}

void TicTacToe::drawUI() {
	std::stringstream coutBuffer;
	coutBuffer << "█▄▀ █▀█ █▀▀ █▀▀ ▀█▀ █ ▄█ █▄▀ █ ▄█  ▄▄  █ █ █▀█  █▀█ █ ▄█ █▄▀ █ ▄█" << '\n';
	coutBuffer << "█ █ █▀▀ ██▄ █▄▄  █  █▀ █ █ █ █▀ █      █▀█ █▄█ ▄█ █ █▀ █ █ █ █▀ █" << '\n';
	coutBuffer << gridSize_ * gridSizeHeightMultiplier_ << " | " << gridSize_ * gridSizeWidthMultiplier_ << '\n';
	coutBuffer << getGridUI();
	std::cout << coutBuffer.str();
}

std::string TicTacToe::getGridUI() {
	std::string gridBufferStr;
	int cellCount{};
	bool isBeginCell = false;
	bool isEndCell = false;
	for (int i = 1; i <= gridSize_ * gridSizeHeightMultiplier_; ++i)
	{

		if (i % gridSizeHeightMultiplier_ == 0 && i < gridSize_ * gridSizeHeightMultiplier_)
		{
			for (int k = 1; k <= gridSize_; ++k)
			{
				for (int j = 1; j <= gridSizeWidthMultiplier_; ++j)
				{
					gridBufferStr += "─";
				}
				gridBufferStr += k == gridSize_ ? "" : "┼";
			}
		}
		else
		{
			if ((i + 1) % gridSizeHeightMultiplier_ == 0)
			{
				cellCount -= gridSize_;
			}
			for (int k = 1; k <= gridSize_; ++k)
			{
				if ((i - 1) % gridSizeHeightMultiplier_ == 0)
				{
					isBeginCell = true;
				}
				else if ((i + 1) % gridSizeHeightMultiplier_ == 0)
				{
					isEndCell = true;
				}
				for (int j = 1; j <= gridSizeWidthMultiplier_; ++j)
				{
					if (j == 1 && isBeginCell)
					{
						//gridBufferStr += std::to_string(cellCount);
						gameGridCoords_.at(cellCount++);
						isBeginCell = false;
					}
					else if (j == gridSizeWidthMultiplier_ && isEndCell) {
						//gridBufferStr += std::to_string(cellCount);
						isEndCell = false;
					}
					gridBufferStr += " ";
				}
				gridBufferStr += k >= gridSize_ ? "" : "│";
			}
		}

		gridBufferStr += '\n';
	}
	return gridBufferStr;
}

void ticTacToe() {
	TicTacToe game;
	game.startRound();
}
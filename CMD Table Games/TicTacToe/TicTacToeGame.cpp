// TicTacToe - игра крестики-нолики.
// Цели реализации игры:
//  - интерфейс игры
//     * большое название игры							| +
//     * игровая сетка									| +
//	   * счёт и раунд									|
//     * чей ход										|
//	   * кнопка выхода в меню							|
//	   * кнопка выбора сложности						|
//	- функциональная игровая сетка						|
//	   * хранить информацию об статусе каждой ячейки	| +-
//     * хранить информацию об координатах ячеек		| +
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
	gameGridCoords_.assign((size_t)(gridSize_ * gridSize_), {0, 0, 0, 0});
	gameGridStats_.assign((size_t)(gridSize_ * gridSize_), CellStatus(CellStatus::empty));
	gridSizeWidthMultiplier_ = (getConsoleWidth() - gridSize_) / gridSize_;
	gridSizeHeightMultiplier_ = (getConsoleHeight() - 10) / gridSize_;
}

void TicTacToe::startRound() {
	static std::string hideCursor = "\033[?25l\n";
	std::cout << hideCursor;
	for (;;)
	{
		clearScreen();
		//system("cls");
		drawUI();
		mouseEventWaiting();
	}
}

void TicTacToe::drawUI() {
	std::stringstream coutBuffer;
	coutBuffer << "█▄▀ █▀█ █▀▀ █▀▀ ▀█▀ █ ▄█ █▄▀ █ ▄█  ▄▄  █ █ █▀█  █▀█ █ ▄█ █▄▀ █ ▄█" << '\n';
	coutBuffer << "█ █ █▀▀ ██▄ █▄▄  █  █▀ █ █ █ █▀ █      █▀█ █▄█ ▄█ █ █▀ █ █ █ █▀ █" << '\n';
	coutBuffer << gridSize_ * gridSizeHeightMultiplier_ << " | " << gridSize_ * gridSizeWidthMultiplier_ << '\n';
	coutBuffer << getEmptyGridUI(0, 3);
	std::cout << coutBuffer.str();
}

std::string TicTacToe::getEmptyGridUI(int xOffset, int yOffset) {
	//CONSOLE_SCREEN_BUFFER_INFO csbi;
	//GetConsoleScreenBufferInfo(getHandleOutput(), &csbi);
	std::string gridBufferStr;
	int cellCount{};
	int cellCol {1};
	int cellRow {1};
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
			++cellRow;
			cellCol = 1;
		}
		else
		{
			if ((i + 1) % gridSizeHeightMultiplier_ == 0)
			{
				cellCount -= gridSize_;
				cellCol -= gridSize_;
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
						gameGridCoords_.at(cellCount).Left = xOffset + gridSizeWidthMultiplier_ * (cellCol++ - 1);
						gameGridCoords_.at(cellCount++).Top = yOffset + gridSizeHeightMultiplier_ * (cellRow - 1);
						isBeginCell = false;
					}
					else if (j == gridSizeWidthMultiplier_ && isEndCell) {
						//gridBufferStr += std::to_string(cellCount);
						gameGridCoords_.at(cellCount).Right = (gridSizeWidthMultiplier_ - 1) * cellCol++;
						gameGridCoords_.at(cellCount++).Bottom = (gridSizeHeightMultiplier_ + 1) * cellRow;
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

void TicTacToe::mouseEventWaiting() {
	HANDLE hInput = getHandleInput();
	INPUT_RECORD inputBufferRecord;
	DWORD numRead;
	DWORD numEvents{};

	for (;;)
	{
		//GetNumberOfConsoleInputEvents(hInput, &numEvents);
		//if (numEvents == 0) continue;

		ReadConsoleInput(hInput, &inputBufferRecord, 1, &numRead);
		if (inputBufferRecord.EventType == MOUSE_EVENT)
		{
			MOUSE_EVENT_RECORD mer = inputBufferRecord.Event.MouseEvent;
			SHORT x = mer.dwMousePosition.X;
			SHORT y = mer.dwMousePosition.Y;
			if (isMouseOnCell(x, y))
			{
				int cellId = getCell(x, y);
				setCell(CellStatus::focus, cellId);
				std::cout << "\n\rна клетке: " << + 1 << " | " << x << ", " << y;
			}
			else
			{
				std::cout << "\n\rне на клетке " << x << ", " << y;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			break;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}

bool TicTacToe::isMouseOnCell(SHORT x, SHORT y) {
	for (auto coords : gameGridCoords_)
	{
		if (x >= coords.Left && y >= coords.Top && x <= coords.Right && y <= coords.Bottom)
		{
			return true;
		}
	}
	return false;
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

void TicTacToe::setCell(CellStatus cs, int id) {
	if (id < 0 || id >= gameGridStats_.size()) return;
	gameGridStats_.at(id) = cs;
}


void ticTacToe() {
	TicTacToe game;
	game.startRound();
}
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
//	   * взаимодействие через нажатие мышки				| +-
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
#include <ranges>
#include <cmath>
#include <string>
#include <sstream>
#include <exception>
#include "TicTacToeGame.h"
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
		drawUI();
		mouseEventWaiting();
	}
}

void TicTacToe::drawUI() {
	for(;;)
	{
		std::stringstream coutBuffer;
		coutBuffer << "█▄▀ █▀█ █▀▀ █▀▀ ▀█▀ █ ▄█ █▄▀ █ ▄█  ▄▄  █ █ █▀█  █▀█ █ ▄█ █▄▀ █ ▄█" << '\n';
		coutBuffer << "█ █ █▀▀ ██▄ █▄▄  █  █▀ █ █ █ █▀ █      █▀█ █▄█ ▄█ █ █▀ █ █ █ █▀ █" << '\n';
		coutBuffer << '\n';
		int existingLinesInBuffer = std::ranges::count(coutBuffer.str(), '\n');
		if (gridSize_ >= 10 || gridSizeHeightMultiplier_ <= 2)
		{
			int centeredSmallOffsetX = (getConsoleWidth() - (gridSize_ * 4 - 1)) / 2;
			//int centeredSmallOffsetY = (getConsoleHeight() - (gridSize_ * 2 - 1)) / 2;
			coutBuffer << getSmallGridUI(centeredSmallOffsetX, 1, existingLinesInBuffer);
		}
		else
		{
			int centeredBigOffsetX = (getConsoleWidth() - (gridSize_ * gridSizeWidthMultiplier_ + (gridSize_ - 1))) / 2;
			//int centeredBigOffsetY = (getConsoleHeight() - (gridSize_ * gridSizeHeightMultiplier_ + (gridSize_ - 1))) / 2;
			coutBuffer << getBigGridUI(centeredBigOffsetX, 1, existingLinesInBuffer);
		}
		existingLinesInBuffer = std::ranges::count(coutBuffer.str(), '\n');
		if (existingLinesInBuffer >= getConsoleHeight())
		{
			--gridSizeHeightMultiplier_;
			gridSizeWidthMultiplier_ -= 2;
		}
		else
		{
			std::cout << coutBuffer.str();
			break;
		}
	}
}

std::string TicTacToe::getSmallGridUI(int xOffset, int yOffset, int existingLinesNum) {
	std::string gridBufferStr;
	yOffset = (std::max)(yOffset, 0);
	gridBufferStr += std::string(yOffset, '\n');
	yOffset += existingLinesNum;
	for (int i{}; i < gridSize_; ++i)
	{
		int cellCoordX = xOffset;
		gridBufferStr += std::string(xOffset, ' ');
		for (int k = i * gridSize_; k < (i + 1) * gridSize_; ++k)
		{
			gameGridCoords_.at(k).Left = cellCoordX;
			gameGridCoords_.at(k).Top = i * 2 + yOffset;
			gameGridCoords_.at(k).Right = cellCoordX + 2;
			gameGridCoords_.at(k).Bottom = i * 2 + yOffset;
			if (gameGridStats_.at(k) == CellStatus::empty)
			{
				gridBufferStr += "   ";
			}
			else if (gameGridStats_.at(k) == CellStatus::focus)
			{
				if (stepCount_ % 2 != 0)
				{
					gridBufferStr += " ╳ ";
				}
				else
				{
					gridBufferStr += " ◯ ";
				}
			}
			gridBufferStr += (k == (i + 1) * gridSize_ - 1 ? "" : "│");
			cellCoordX += 4;
		}
		gridBufferStr += "\n";
		if (i == gridSize_ - 1) continue;
		gridBufferStr += std::string(xOffset, ' ');
		for (int j = i * gridSize_; j < (i + 1) * gridSize_; ++j)
		{
			gridBufferStr += "───";
			gridBufferStr += (j == (i + 1) * gridSize_ - 1 ? "" : "┼");
		}
		gridBufferStr += "\n";
	}
	return gridBufferStr;
}


std::string TicTacToe::getBigGridUI(int xOffset, int yOffset, int existingLinesNum) {
	std::string gridBufferStr;
	int cellCount{};
	int accurateCellCount{};
	int charColCount{};
	int charRowCount{};
	bool isBeginCell = false;
	bool isEndCell = false;
	yOffset = (std::max)(yOffset, 0);
	gridBufferStr += std::string(yOffset, '\n');
	yOffset += existingLinesNum;
	for (int i = 1; i <= gridSize_ * gridSizeHeightMultiplier_; ++i)
	{
		gridBufferStr += std::string(xOffset, ' ');
		if ((i + 1) % gridSizeHeightMultiplier_ == 0)
		{
			++charRowCount;
			cellCount -= gridSize_;
			cellCount = std::clamp(cellCount, 0, gridSize_ * gridSize_);
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
					gameGridCoords_.at(cellCount).Left = xOffset + charColCount;
					gameGridCoords_.at(cellCount).Top = yOffset + charRowCount;
					++cellCount;
					isBeginCell = false;
				}
				else if (j == gridSizeWidthMultiplier_ && isEndCell)
				{
					//gridBufferStr += std::to_string(cellCount);
					gameGridCoords_.at(cellCount).Right = xOffset + charColCount;
					gameGridCoords_.at(cellCount).Bottom = yOffset + charRowCount;
					++cellCount;
					isEndCell = false;
				}
				if (gameGridStats_.at(accurateCellCount) == CellStatus::empty)
				{
					gridBufferStr += " ";
				}
				else if(gameGridStats_.at(accurateCellCount) == CellStatus::focus)
				{
					if (stepCount_ % 2 != 0)
					{
						gridBufferStr += "X";
					}
					else
					{
						gridBufferStr += "O";
					}
				}
				++charColCount;
			}
			gridBufferStr += k >= gridSize_ ? "" : "│";
			accurateCellCount += k >= gridSize_ ? 0 : 1;
			++charColCount;
		}
		accurateCellCount -= (gridSize_ - 1);
		charColCount = 0;
		gridBufferStr += '\n';
		++charRowCount;

		if (i % gridSizeHeightMultiplier_ == 0 && i < gridSize_ * gridSizeHeightMultiplier_)
		{
			gridBufferStr += std::string(xOffset, ' ');
			for (int k = 1; k <= gridSize_; ++k)
			{
				for (int j = 1; j <= gridSizeWidthMultiplier_; ++j)
				{
					gridBufferStr += "─";
				}
				gridBufferStr += k == gridSize_ ? "" : "┼";
			}
			accurateCellCount += gridSize_;
			gridBufferStr += '\n';
		}
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
				if (focusedCellId_ != -1)
				{
					setCell(CellStatus::empty, focusedCellId_);
				}
				focusedCellId_ = getCell(x, y);
				if(getCellStatus(focusedCellId_) == CellStatus::empty)
				{
					setCell(CellStatus::focus, focusedCellId_);
				}
				//std::cout << "\n\rна клетке: " << focusedCellId_ + 1 << " | " << x << ", " << y;
				//std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
			else
			{
				if (focusedCellId_ != -1)
				{
					setCell(CellStatus::empty, focusedCellId_);
				}
				//std::cout << "\n\rне на клетке " << x << ", " << y;
				//std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
			break;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
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
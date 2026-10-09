// TicTacToe - игра крестики-нолики.
// Задачи для реализации игры:
//  - интерфейс игры									| +-
//     * большое название игры							| +
//     * игровая сетка									| +
//	   * счёт и раунд									| +
//     * чей ход										| +
//	   * кнопка рестарта								| +
//	   * кнопка выхода в меню							|
//	   * кнопка выбора сложности						| +
//	   * кнопка изменения размера поля					|
//	- функциональная игровая сетка						| +
//	   * хранить информацию об статусе каждой ячейки	| +
//     * хранить информацию об координатах ячеек		| +
//	   * взаимодействие через нажатие мышки				| +
//  - выбор соперника									| +-
//	   * соперник второй игрок							|
//	   * соперник бот									| +-
//       ~ лёгкая сложность (рандом)					| +
//	     ~ средняя сложность (50% алгоритм, 50% рандом) |
//       ~ высокая сложная (95% - алгоритм)				|
//

#include <iostream>
#include <algorithm>
#include <string>
#include <exception>
#include <vector>
#include "Headers/TicTacToeGame.h"
#include "Common/ConsoleWindow.h"

TicTacToe::TicTacToe(int gameGridSize)
	: ConsoleWindow::ConsoleWindow(65, 45, L"Крестики-Нолики") {
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
	for(;;)
	{
		if (isRestartRequired_ == false || gameResult_ != GameResult::notDefined)
		{
			++roundCount_;
			if (gameResult_ == GameResult::win)
			{
				++scorePlayer_;
			}
			else if (gameResult_ == GameResult::lose)
			{
				if (bot.mode_ == Bot::Modes::off)
				{
					++scoreSecondPlayer_;
				}
				else
				{
					++scoreBot_;
				}
			}
		}
		isRestartRequired_ = false;
		gameGridCoords_.assign((size_t)(gridSize_ * gridSize_), { 0, 0, 0, 0 });
		gameGridStats_.assign((size_t)(gridSize_ * gridSize_), CellStatus(CellStatus::empty));
		static std::string hideCursor = "\033[?25l\n";
		std::cout << hideCursor;
		stepCount_ = 0;
		gameResult_ = GameResult::notDefined;
		isPlayerFirst = true;
		isPlayerTurn = isPlayerFirst;
		//bot.mode_ = Bot::Modes::easy;
		for (; isRestartRequired_ == false;)
		{
			setCursorPos(0, 0); // убирает мерцание, но нужно следить за некоторыми моментами
			//clearScreen(); // мерцает 
			//system("cls"); // мерцает + медленно
			auto& buttons = gameUI.drawUI(*this);
			if (isPlayerTurn)
			{
				if (mouseInter.mouseEventWaiting(*this, buttons))
				{
					gameResult_ = checkGameResult();
					isPlayerTurn = false;
				}
			}
			else
			{
				if (bot.mode_ != Bot::Modes::off)
				{
					bot.makeMove(*this);
					gameResult_ = checkGameResult();
					isPlayerTurn = true;
				}
				else if (mouseInter.mouseEventWaiting(*this, buttons))
				{
					gameResult_ = checkGameResult();
					isPlayerTurn = true;
				}
			}
		}
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

TicTacToe::GameResult TicTacToe::checkGameResult() {
	int repeatsThreshold = std::clamp(gridSize_, 3, 5);

	if (stepCount_ < repeatsThreshold * 2 - 1) return GameResult::notDefined;
	if (gameResult_ == GameResult::win || gameResult_ == GameResult::lose) return gameResult_;

	int cellId{};

	int colRepeats{};
	for (int row{}; row < gridSize_; ++row)
	{
		colRepeats = 0;
		for (int col{}; col < gridSize_; ++col)
		{
			auto currentColCell = getCellStatus(cellId);
			if (col + 1 == gridSize_) 
			{
				++cellId;
				break;
			}
			auto nextColCell = getCellStatus(cellId + 1);
			if (currentColCell == nextColCell &&
				(currentColCell == CellStatus::cross || currentColCell == CellStatus::zero))
			{
				colRepeats += colRepeats == 0 ? 2 : 1;
			}
			else colRepeats = 0;

			if (colRepeats == repeatsThreshold)
			{
				return isPlayerFirst && stepCount_ % 2 != 0 ? GameResult::win : GameResult::lose;
			}
			++cellId;
		}
	}

	int rowRepeats{};
	for (int col{}; col < gridSize_; ++col)
	{
		rowRepeats = 0;
		cellId = col;
		for (int row{}; row < gridSize_; ++row)
		{
			auto currentRowCell = getCellStatus(cellId);
			if (row + 1 == gridSize_) break;
			cellId += gridSize_;
			auto nextRowCell = getCellStatus(cellId);
			if (currentRowCell == nextRowCell &&
				(currentRowCell == CellStatus::cross || currentRowCell == CellStatus::zero))
			{
				rowRepeats += rowRepeats == 0 ? 2 : 1;
			}
			else rowRepeats = 0;

			if (rowRepeats == repeatsThreshold)
			{
				return isPlayerFirst && stepCount_ % 2 != 0 ? GameResult::win : GameResult::lose;
			}
		}
	}

	int diagRepeats{};
	for (int colOffset = repeatsThreshold - 1; colOffset < gridSize_ + (gridSize_ - repeatsThreshold); ++colOffset)
	{
		if (colOffset > gridSize_ - 1)
		{
			cellId = gridSize_ - 1;
			for (int i = colOffset - (gridSize_ - 1); i > 0; --i)
			{
				cellId += cellId + gridSize_ >= gridSize_ * gridSize_ ? 0 : gridSize_;
			}
		}
		else
		{
			cellId = colOffset;
		}
		diagRepeats = 0;
		while (cellId % gridSize_ != 0)
		{
			auto currentCell = getCellStatus(cellId);
			cellId += gridSize_ - 1;
			if (cellId >= gridSize_ * gridSize_) break;
			auto nextCell = getCellStatus(cellId);
			if (currentCell == nextCell &&
				(currentCell == CellStatus::cross || currentCell == CellStatus::zero))
			{
				diagRepeats += diagRepeats == 0 ? 2 : 1;
			}
			else diagRepeats = 0;

			if (diagRepeats == repeatsThreshold)
			{
				return isPlayerFirst && stepCount_ % 2 != 0 ? GameResult::win : GameResult::lose;
			}
		}
	}
	for (int colOffset = gridSize_ - repeatsThreshold; colOffset >= repeatsThreshold - gridSize_; --colOffset)
	{
		if (colOffset < 0)
		{
			cellId = 0;
			for (int i = colOffset; i < 0; ++i)
			{
				cellId += cellId + gridSize_ >= gridSize_ * gridSize_ ? 0 : gridSize_;
			}
		}
		else
		{
			cellId = colOffset;
		}
		diagRepeats = 0;
		do
		{
			auto currentCell = getCellStatus(cellId);
			cellId += gridSize_ + 1;
			if (cellId >= gridSize_ * gridSize_) break;
			auto nextCell = getCellStatus(cellId);
			if (currentCell == nextCell &&
				(currentCell == CellStatus::cross || currentCell == CellStatus::zero))
			{
				diagRepeats += diagRepeats == 0 ? 2 : 1;
			}
			else diagRepeats = 0;

			if (diagRepeats == repeatsThreshold)
			{
				return isPlayerFirst && stepCount_ % 2 != 0 ? GameResult::win : GameResult::lose;
			}
		} while (cellId % (gridSize_ - 1) != 0 || (cellId + gridSize_) < (gridSize_ * gridSize_));
	}
	if (stepCount_ == gridSize_ * gridSize_)
	{
		return GameResult::draw;
	}
	else return GameResult::notDefined;
}



void ticTacToe() {
	TicTacToe game(3);
	game.startRound();
}
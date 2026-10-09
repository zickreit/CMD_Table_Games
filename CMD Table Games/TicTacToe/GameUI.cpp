#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <ranges>
#include "Headers/TicTacToeModules.h"
#include "Headers/TicTacToeGame.h"
#include "Common/Button.h"

std::vector<Button>& GameUI::drawUI(TicTacToe& game) {
	for(int i{}; i < otherUI.buttons_.size(); ++i)
	{
		otherUI.buttons_.at(i).setDrawedState(false);
		if (otherUI.buttons_.at(i).getState() == Button::State::pressed)
		{
			otherUI.implementButtonAction(game, i);
		}
	}
	if(game.isRestartRequired_) 
	{
		return otherUI.buttons_;
	}
	for (;;)
	{
		std::stringstream coutBuffer;
		if (game.getConsoleWidth() >= 65)
		{
			coutBuffer << std::string((game.getConsoleWidth() - 65) / 2, ' ') << "█▄▀ █▀█ █▀▀ █▀▀ ▀█▀ █ ▄█ █▄▀ █ ▄█  ▄▄  █ █ █▀█  █▀█ █ ▄█ █▄▀ █ ▄█" << '\n';
			coutBuffer << std::string((game.getConsoleWidth() - 65) / 2, ' ') << "█ █ █▀▀ ██▄ █▄▄  █  █▀ █ █ █ █▀ █      █▀█ █▄█ ▄█ █ █▀ █ █ █ █▀ █" << '\n';
			coutBuffer << '\n';
		}
		else if (game.getConsoleWidth() >= 17)
		{
			coutBuffer << "Крестики - Нолики\n";
		}
		else if (game.getConsoleWidth() >= 8)
		{
			coutBuffer << "Крестики\nНолики\n";
		}
		int existingLinesInBuffer = std::ranges::count(coutBuffer.str(), '\n');

		if (/*game.gridSize_ >= 10 || */game.gridSizeHeightMultiplier_ <= 2)
		{
			int centeredSmallOffsetX = (game.getConsoleWidth() - (game.gridSize_ * 4 - 1)) / 2;
			//int centeredSmallOffsetY = (getConsoleHeight() - (gridSize_ * 2 - 1)) / 2;
			coutBuffer << gridUI.getSmallGridUI(game, centeredSmallOffsetX, 1, existingLinesInBuffer);
		}
		else
		{
			int centeredBigOffsetX = (game.getConsoleWidth() - (game.gridSize_ * game.gridSizeWidthMultiplier_ + (game.gridSize_ - 1))) / 2;
			//int centeredBigOffsetY = (getConsoleHeight() - (gridSize_ * gridSizeHeightMultiplier_ + (gridSize_ - 1))) / 2;
			coutBuffer << gridUI.getBigGridUI(game, centeredBigOffsetX, 1, existingLinesInBuffer);
		}
		existingLinesInBuffer = std::ranges::count(coutBuffer.str(), '\n');
		if (existingLinesInBuffer >= game.getConsoleHeight() || game.gridSize_ * game.gridSizeWidthMultiplier_ + (game.gridSize_ - 1) >= game.getConsoleWidth())
		{
			--game.gridSizeHeightMultiplier_;
			game.gridSizeWidthMultiplier_ -= 2;
		}
		else if (existingLinesInBuffer + game.gridSize_ * game.gridSizeHeightMultiplier_ + (game.gridSize_ - 1) < game.getConsoleHeight()
				 && game.gridSize_ * game.gridSizeWidthMultiplier_ + (game.gridSize_ - 1) < game.getConsoleWidth())
		{
			++game.gridSizeHeightMultiplier_;
			game.gridSizeWidthMultiplier_ += 2;
		}
		else
		{
			std::cout << coutBuffer.str();
			if (game.gameResult_ == TicTacToe::GameResult::notDefined)
			{
				std::cout << "Не завершено!";
			}
			else if (game.gameResult_ == TicTacToe::GameResult::draw)
			{
				std::cout << "Ничья!";
			}
			else if (game.gameResult_ == TicTacToe::GameResult::lose)
			{
				std::cout << "Проигрыш!";
			}
			else if (game.gameResult_ == TicTacToe::GameResult::win)
			{
				std::cout << "Победа!";
			}
			std::cout << "\033[K | Раунд: " << game.roundCount_;
			if(game.bot.mode_ != Bot::Modes::off)
			{
				std::cout << "\033[K";
				std::cout << " | Счёт игрока: " << game.scorePlayer_ << " | Счёт бота: " << game.scoreBot_ << '\n';
				std::cout << (game.isPlayerTurn ? "Ход игрока\033[K\n" : "Ход бота\033[K\n");
			}
			else
			{
				std::cout << "\033[K";
				std::cout << " | Счёт игрока 1: " << game.scorePlayer_ << " | Счёт игрока 2: " << game.scoreSecondPlayer_ << '\n';
				std::cout << (game.isPlayerTurn ? "Ход игрока 1\033[K\n" : "Ход игрока 2\033[K\n");
			}
			CONSOLE_SCREEN_BUFFER_INFO csbi;
			GetConsoleScreenBufferInfo(game.getHandleOutput(), &csbi);
			std::cout << otherUI.buttons_.at(0).drawButton(0, csbi.dwCursorPosition.Y) << " | ";
			GetConsoleScreenBufferInfo(game.getHandleOutput(), &csbi);
			std::cout << otherUI.buttons_.at(1).drawButton(csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y) << " | ";
			GetConsoleScreenBufferInfo(game.getHandleOutput(), &csbi);
			std::cout << otherUI.buttons_.at(6).drawButton(csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y);
			if (otherUI.buttons_.at(1).getSwitchState() == 1)
			{
				std::cout << "\n";
				GetConsoleScreenBufferInfo(game.getHandleOutput(), &csbi);
				std::cout << otherUI.buttons_.at(2).drawButton(0, csbi.dwCursorPosition.Y) << " | ";
				GetConsoleScreenBufferInfo(game.getHandleOutput(), &csbi);
				std::cout << otherUI.buttons_.at(3).drawButton(csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y) << " | ";
				GetConsoleScreenBufferInfo(game.getHandleOutput(), &csbi);
				std::cout << otherUI.buttons_.at(4).drawButton(csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y) << " | ";
				GetConsoleScreenBufferInfo(game.getHandleOutput(), &csbi);
				std::cout << otherUI.buttons_.at(5).drawButton(csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y);
			}
			else if (otherUI.buttons_.at(6).getSwitchState() == 1)
			{
				std::cout << "\n";
				GetConsoleScreenBufferInfo(game.getHandleOutput(), &csbi);
				std::cout << otherUI.buttons_.at(7).drawButton(0, csbi.dwCursorPosition.Y) << " | ";
				GetConsoleScreenBufferInfo(game.getHandleOutput(), &csbi);
				std::cout << otherUI.buttons_.at(8).drawButton(csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y) << " | ";
				GetConsoleScreenBufferInfo(game.getHandleOutput(), &csbi);
				std::cout << otherUI.buttons_.at(9).drawButton(csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y) << " | ";
				GetConsoleScreenBufferInfo(game.getHandleOutput(), &csbi);
				std::cout << otherUI.buttons_.at(10).drawButton(csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y);
				std::cout << "\n\r\033[K";
			}
			else
			{
				std::cout << "\n\r\033[K";
			}
			return otherUI.buttons_;
		}
	}
}
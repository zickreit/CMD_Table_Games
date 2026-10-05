#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <ranges>
#include "Headers/TicTacToeModules.h"
#include "Headers/TicTacToeGame.h"

void GameUI::drawUI(TicTacToe& game) {
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
		if (game.gridSize_ >= 10 || game.gridSizeHeightMultiplier_ <= 2)
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
			break;
		}
	}
}
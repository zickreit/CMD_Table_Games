#include <string>
#include <algorithm>
#include "Headers/TicTacToeModules.h"
#include "Headers/TicTacToeGame.h"

std::string GridUI::getSmallGridUI(TicTacToe& game, int xOffset, int yOffset, int existingLinesNum) {
	std::string gridBufferStr;
	yOffset = (std::max)(yOffset, 0);
	xOffset = (std::max)(xOffset, 0);
	gridBufferStr += std::string(yOffset, '\n');
	yOffset += existingLinesNum;
	for (int i{}; i < game.gridSize_; ++i)
	{
		int cellCoordX = xOffset;
		gridBufferStr += std::string(xOffset, ' ');
		for (int k = i * game.gridSize_; k < (i + 1) * game.gridSize_; ++k)
		{
			game.gameGridCoords_.at(k).Left = cellCoordX;
			game.gameGridCoords_.at(k).Top = i * 2 + yOffset;
			game.gameGridCoords_.at(k).Right = cellCoordX + 2;
			game.gameGridCoords_.at(k).Bottom = i * 2 + yOffset;
			if (game.gameGridStats_.at(k) == TicTacToe::CellStatus::empty)
			{
				gridBufferStr += "   ";
			}
			else if (game.gameGridStats_.at(k) == TicTacToe::CellStatus::focus)
			{
				if (game.stepCount_ % 2 != 0)
				{
					gridBufferStr += " ╳ ";
				}
				else
				{
					gridBufferStr += " ◯ ";
				}
			}
			else if (game.gameGridStats_.at(k) == TicTacToe::CellStatus::cross)
			{
				gridBufferStr += " ╳ ";
			}
			else if (game.gameGridStats_.at(k) == TicTacToe::CellStatus::cross)
			{
				gridBufferStr += " ◯ ";
			}
			gridBufferStr += (k == (i + 1) * game.gridSize_ - 1 ? "" : "│");
			cellCoordX += 4;
		}
		gridBufferStr += "\n";
		if (i == game.gridSize_ - 1) continue;
		gridBufferStr += std::string(xOffset, ' ');
		for (int j = i * game.gridSize_; j < (i + 1) * game.gridSize_; ++j)
		{
			gridBufferStr += "───";
			gridBufferStr += (j == (i + 1) * game.gridSize_ - 1 ? "" : "┼");
		}
		gridBufferStr += "\n";
	}
	return gridBufferStr;
}

std::string GridUI::getBigGridUI(TicTacToe& game, int xOffset, int yOffset, int existingLinesNum) {
	std::string gridBufferStr;
	int cellCount{};
	int accurateCellCount{};
	int charColCount{};
	int charRowCount{};
	bool isBeginCell = false;
	bool isEndCell = false;
	yOffset = (std::max)(yOffset, 0);
	xOffset = (std::max)(xOffset, 0);
	gridBufferStr += std::string(yOffset, '\n');
	yOffset += existingLinesNum;
	for (int i = 1; i <= game.gridSize_ * game.gridSizeHeightMultiplier_; ++i)
	{
		gridBufferStr += std::string(xOffset, ' ');
		if ((i + 1) % game.gridSizeHeightMultiplier_ == 0)
		{
			++charRowCount;
			cellCount -= game.gridSize_;
			cellCount = std::clamp(cellCount, 0, game.gridSize_ * game.gridSize_);
		}
		for (int k = 1; k <= game.gridSize_; ++k)
		{
			if ((i - 1) % game.gridSizeHeightMultiplier_ == 0)
			{
				isBeginCell = true;
			}
			else if ((i + 1) % game.gridSizeHeightMultiplier_ == 0)
			{
				isEndCell = true;
			}
			for (int j = 1; j <= game.gridSizeWidthMultiplier_; ++j)
			{
				if (j == 1 && isBeginCell)
				{
					//gridBufferStr += std::to_string(cellCount);
					game.gameGridCoords_.at(cellCount).Left = xOffset + charColCount;
					game.gameGridCoords_.at(cellCount).Top = yOffset + charRowCount;
					++cellCount;
					isBeginCell = false;
				}
				else if (j == game.gridSizeWidthMultiplier_ && isEndCell)
				{
					//gridBufferStr += std::to_string(cellCount);
					game.gameGridCoords_.at(cellCount).Right = xOffset + charColCount;
					game.gameGridCoords_.at(cellCount).Bottom = yOffset + charRowCount;
					++cellCount;
					isEndCell = false;
				}
				if (game.gameGridStats_.at(accurateCellCount) == TicTacToe::CellStatus::empty)
				{
					gridBufferStr += " ";
				}
				else if (game.gameGridStats_.at(accurateCellCount) == TicTacToe::CellStatus::focus)
				{
					if (game.stepCount_ % 2 != 0)
					{
						gridBufferStr += "X";
					}
					else
					{
						gridBufferStr += "O";
					}
				}
				else if (game.gameGridStats_.at(accurateCellCount) == TicTacToe::CellStatus::cross)
				{
					gridBufferStr += "X";
				}
				else if (game.gameGridStats_.at(accurateCellCount) == TicTacToe::CellStatus::zero)
				{
					gridBufferStr += "O";
				}
				++charColCount;
			}
			gridBufferStr += k >= game.gridSize_ ? "" : "│";
			accurateCellCount += k >= game.gridSize_ ? 0 : 1;
			++charColCount;
		}
		accurateCellCount -= (game.gridSize_ - 1);
		charColCount = 0;
		gridBufferStr += '\n';
		++charRowCount;

		if (i % game.gridSizeHeightMultiplier_ == 0 && i < game.gridSize_ * game.gridSizeHeightMultiplier_)
		{
			gridBufferStr += std::string(xOffset, ' ');
			for (int k = 1; k <= game.gridSize_; ++k)
			{
				for (int j = 1; j <= game.gridSizeWidthMultiplier_; ++j)
				{
					gridBufferStr += "─";
				}
				gridBufferStr += k == game.gridSize_ ? "" : "┼";
			}
			accurateCellCount += game.gridSize_;
			gridBufferStr += '\n';
		}
	}
	return gridBufferStr;
}
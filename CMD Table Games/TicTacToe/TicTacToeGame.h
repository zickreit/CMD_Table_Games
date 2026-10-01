#pragma once
#include <vector>
#include <string>
#include <Windows.h>
#include "Common/ConsoleWindow.h"

class TicTacToe : public ConsoleWindow {
private:
	enum class CellStatus {
		empty,
		cross,
		zero
	};
private:
	std::vector<CellStatus> gameGridStats_;
	std::vector<SMALL_RECT> gameGridCoords_;
	int gridSize_{};
	int gridSizeWidthMultiplier_{};
	int gridSizeHeightMultiplier_{};
public:
	TicTacToe(int gameGridSize = 3);

	void startRound();

	void drawUI();
	std::string getGridUI(int xOffset, int yOffset);

	void mouseEventWaiting();
	bool isMouseOnCell(short x, short y);
};

void ticTacToe();
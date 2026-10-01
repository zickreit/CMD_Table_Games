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
	std::vector<RECT> gameGridCoords_;
	int gridSize_{};
	int gridSizeWidthMultiplier_{};
	int gridSizeHeightMultiplier_{};
public:
	TicTacToe(int gameGridSize = 3);

	void startRound();

	void drawUI();

	std::string getGridUI();
};

void ticTacToe();
#pragma once
#include <vector>
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
	std::vector<std::vector<CellStatus>> gameGridStats_;
	std::vector<std::vector<COORD>> gameGridCoords_;
	int gameGridSize_{};
public:
	TicTacToe(int gameGridSize = 3);

	void startRound();

	void drawInterface();
};

void ticTacToe();
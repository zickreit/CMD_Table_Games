#pragma once
#include <vector>
#include "Common/ConsoleWindow.h"

class TicTacToe : public ConsoleWindow {
private:
	std::vector<std::vector<int>> gameGrid_;
	int gameGridSize_{};
public:
	TicTacToe(int gameGridSize = 3);

	void startRound();
};

void ticTacToe();
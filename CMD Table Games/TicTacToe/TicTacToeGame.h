#pragma once
#include <vector>
#include <string>
#include <Windows.h>
#include "Common/ConsoleWindow.h"

class TicTacToe : public ConsoleWindow {
private:
	enum class CellStatus {
		empty,
		focus,
		cross,
		zero
	};
private:
	std::vector<CellStatus> gameGridStats_;
	std::vector<SMALL_RECT> gameGridCoords_;
	int gridSize_{};
	int gridSizeWidthMultiplier_{};
	int gridSizeHeightMultiplier_{};
	int stepCount_{};
	int focusedCellId_ = -1;
public:
	TicTacToe(int gameGridSize = 3);

	void startRound();

	void drawUI();
	std::string getEmptyGridUI(int xOffset, int yOffset);
	//std::string getFilledCellsUI()

	int getCell(SHORT x, SHORT y);
	void setCell(CellStatus cs, int id);

	void mouseEventWaiting();
	bool isMouseOnCell(short x, short y);
};

void ticTacToe();
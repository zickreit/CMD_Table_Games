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
	std::string getSmallGridUI(int xOffset, int yOffset, int existingLinesNum);
	std::string getBigGridUI(int xOffset, int yOffset, int existingLinesNum);
	//std::string getFilledCellsUI();

	int getCell(SHORT x, SHORT y);
	CellStatus getCellStatus(int id);
	void setCell(CellStatus cs, int id);

	void mouseEventWaiting();
	bool isMouseOnCell(short x, short y);
};

void ticTacToe();
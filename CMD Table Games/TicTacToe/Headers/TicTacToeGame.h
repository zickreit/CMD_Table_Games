#pragma once
#include <vector>
#include <string>
#include <Windows.h>
#include "Common/ConsoleWindow.h"
#include "TicTacToeModules.h"

class TicTacToe : public ConsoleWindow {
	friend class GameUI;
	friend class GridUI;
	friend class MouseInterction;
private:
	enum class CellStatus {
		empty,
		focus,
		cross,
		zero
	};
private:
	GameUI gameUI;
	MouseInterction mouseInter;
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

	int getCell(SHORT x, SHORT y);
	CellStatus getCellStatus(int id);
	void setCell(CellStatus cs, int id);

};

void ticTacToe();
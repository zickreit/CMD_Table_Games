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
	friend class Bot;
private:
	enum class CellStatus {
		empty,
		focus,
		cross,
		zero
	};
	enum class GameResult {
		win,
		lose,
		draw,
		notDefined
	};
private:
	GameUI gameUI{};
	MouseInterction mouseInter;
	Bot mode;
private:
	std::vector<CellStatus> gameGridStats_;
	std::vector<SMALL_RECT> gameGridCoords_;

	int gridSize_{};
	int gridSizeWidthMultiplier_{};
	int gridSizeHeightMultiplier_{};

	int stepCount_{};
	int focusedCellId_ = -1;

	bool isPlayerFirst{};
	GameResult gameResult_{};
public:
	TicTacToe(int gameGridSize = 3);

	void startRound();

	int getCell(SHORT x, SHORT y);
	CellStatus getCellStatus(int id);
	void setCell(CellStatus cs, int id);

	GameResult checkGameResult();
};

void ticTacToe();
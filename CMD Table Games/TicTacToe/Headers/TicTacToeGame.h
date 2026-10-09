#pragma once
#include <vector>
#include <string>
#include <Windows.h>
#include "Common/ConsoleWindow.h"
#include "TicTacToeModules.h"

class TicTacToe : public ConsoleWindow {
	friend class GameUI;
	friend class GridUI;
	friend class OtherUI;
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
		notDefined,
		win,
		lose,
		draw
	};
private:
	GameUI gameUI{};
	MouseInterction mouseInter;
	Bot bot;
private:
	std::vector<CellStatus> gameGridStats_;
	std::vector<SMALL_RECT> gameGridCoords_;

	int gridSize_{};
	int gridSizeWidthMultiplier_{};
	int gridSizeHeightMultiplier_{};

	bool isRestartRequired_{};
	int stepCount_{};
	int focusedCellId_ = -1;

	bool isPlayerTurn{};
	bool isPlayerFirst{};
	GameResult gameResult_{};

	int scorePlayer_{};
	int scoreSecondPlayer_{};
	int scoreBot_{};
	int roundCount_{};
public:
	TicTacToe(int gameGridSize = 3);

	void startRound();

	int getCell(SHORT x, SHORT y);
	CellStatus getCellStatus(int id);
	void setCell(CellStatus cs, int id);
	void setRestartRequirement(bool state) { isRestartRequired_ = state; }
	void setGridSize(int newSize);

	GameResult checkGameResult();
};

void ticTacToe();
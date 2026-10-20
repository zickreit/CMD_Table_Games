#pragma once

#include <string>
#include <vector>
#include "TicTacToeGame.h"


class Bot {
	friend class GameUI;
	friend class TicTacToe;
	struct CombinationInfo {
		std::vector<int> cellsId;
		int score{};
		int movesNum{};
		CombinationInfo() = default;
		CombinationInfo(std::vector<int> cells)
			: cellsId(cells) {}
	};
public:
	enum class Modes {
		hard,
		medium,
		easy,
		off
	};
private:
	Bot() = default;
	Modes mode_{};
	std::vector<TicTacToe::CellStatus> simGridStats_;
	int simSteps_{};
public:
	void makeMove(TicTacToe& game);
	int getCellIdEasyMode(TicTacToe& game);
	int getCellIdMediumMode(TicTacToe& game);
	int getCellIdHardMode(TicTacToe& game, int simNum = 5, int forwardMovesNum = 2);
	Modes getMode() { return mode_; }
	void setMode(Modes mode) { mode_ = mode; }
	TicTacToe::CellStatus getSimCellStatus(int id);
};
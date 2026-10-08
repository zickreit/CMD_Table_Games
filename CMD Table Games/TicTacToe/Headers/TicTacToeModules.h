#pragma once

#include <string>
#include <vector>
#include "Common/Button.h"


class TicTacToe;

class OtherUI {
	friend class GameUI;
private:
	OtherUI();
	std::vector<Button> buttons_;
public:
	int getButtonId(short x, short y);
	void implementButtonAction(TicTacToe& game, int id);
};

class GridUI {
	friend class GameUI;
private:
	GridUI() = default;
public:
	std::string getSmallGridUI(TicTacToe& game, int xOffset, int yOffset, int existingLinesNum);
	std::string getBigGridUI(TicTacToe& game, int xOffset, int yOffset, int existingLinesNum);
	std::string getZeroChar(TicTacToe& game, int cellID, int colCount, int rowCount);
	std::string getCrossChar(TicTacToe& game, int cellID, int colCount, int i);
	std::string colorizeChar(std::string&& ch, const std::string& color);
};

class GameUI {
	friend class TicTacToe;
private:
	GameUI() = default;
	OtherUI otherUI;
	GridUI gridUI;
public:
	std::vector<Button>& drawUI(TicTacToe& game);
};

class MouseInterction {
	friend class TicTacToe;
private:
	MouseInterction() = default;
public:
	bool mouseEventWaiting(TicTacToe& game, std::vector<Button>& buttons);
	int getButtonId(const std::vector<Button>& buttons, short x, short y);
	bool isMouseOnCell(TicTacToe& game, short x, short y);
};

class Bot {
	friend class GameUI;
	friend class TicTacToe;
public:
	enum class Modes {
		off,
		easy,
		medium,
		hard
	};
private:
	Bot() = default;
	Modes mode_{};
public:
	void makeMove(TicTacToe& game);
	int getCellIdEasyMode(TicTacToe& game);
	int getCellIdMediumMode(TicTacToe& game);
	int getCellIdHardMode(TicTacToe& game);
	Modes getMode() { return mode_; }
	void setMode(Modes mode) { mode_ = mode; }
};
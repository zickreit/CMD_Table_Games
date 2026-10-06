#pragma once

#include <string>

class TicTacToe;

class OtherUI {
	friend class GameUI;
private:
	OtherUI() = default;
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
	std::string colorizeChar(std::string&& ch, std::string& color);
};

class GameUI {
	friend class TicTacToe;
private:
	GameUI() = default;
	OtherUI otherUI;
	GridUI gridUI;
public:
	void drawUI(TicTacToe& game);
};

class MouseInterction {
	friend class TicTacToe;
private:
	MouseInterction() = default;
public:
	bool mouseEventWaiting(TicTacToe& game);
	bool isMouseOnCell(TicTacToe& game, short x, short y);
};

class Bot {
	friend class TicTacToe;
private:
	Bot() = default;
	enum class Modes {
		off,
		easy,
		medium,
		hard
	};
	Modes mode_{};
public:
	void makeBotMove();
	int getCellIdEasyMode();
	int getCellIdMediumMode();
	int getCellIdHardMode();
};
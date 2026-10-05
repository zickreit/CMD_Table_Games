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
	void mouseEventWaiting(TicTacToe& game);
	bool isMouseOnCell(TicTacToe& game, short x, short y);
};
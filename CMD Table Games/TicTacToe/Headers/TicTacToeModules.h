#pragma once

#include <string>

class TicTacToe;

class OtherUI {

};

class GridUI {
public:
	std::string getSmallGridUI(TicTacToe& game, int xOffset, int yOffset, int existingLinesNum);
	std::string getBigGridUI(TicTacToe& game, int xOffset, int yOffset, int existingLinesNum);
};

class GameUI {
private:
	OtherUI otherUI;
	GridUI gridUI;
public:
	void drawUI(TicTacToe& game);
};

class MouseInterction {
public:
	void mouseEventWaiting(TicTacToe& game);
	bool isMouseOnCell(TicTacToe& game, short x, short y);
};
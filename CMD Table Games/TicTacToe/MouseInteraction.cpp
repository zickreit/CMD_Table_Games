#include <Windows.h>
#include <thread>
#include <chrono>
#include "Headers/TicTacToeGame.h"

void MouseInterction::mouseEventWaiting(TicTacToe& game) {
	HANDLE hInput = game.getHandleInput();
	INPUT_RECORD inputBufferRecord;
	DWORD numRead;
	DWORD numEvents{};

	for (;;)
	{
		//GetNumberOfConsoleInputEvents(hInput, &numEvents);
		//if (numEvents == 0) continue;

		ReadConsoleInput(hInput, &inputBufferRecord, 1, &numRead);
		if (inputBufferRecord.EventType == MOUSE_EVENT)
		{
			MOUSE_EVENT_RECORD mer = inputBufferRecord.Event.MouseEvent;
			SHORT x = mer.dwMousePosition.X;
			SHORT y = mer.dwMousePosition.Y;
			if (isMouseOnCell(game, x, y))
			{
				if (game.focusedCellId_ != -1)
				{
					game.setCell(TicTacToe::CellStatus::empty, game.focusedCellId_);
				}
				game.focusedCellId_ = game.getCell(x, y);
				if (game.getCellStatus(game.focusedCellId_) == TicTacToe::CellStatus::empty)
				{
					game.setCell(TicTacToe::CellStatus::focus, game.focusedCellId_);
				}
				//std::cout << "\n\rна клетке: " << focusedCellId_ + 1 << " | " << x << ", " << y;
				//std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
			else
			{
				if (game.focusedCellId_ != -1)
				{
					game.setCell(TicTacToe::CellStatus::empty, game.focusedCellId_);
				}
				//std::cout << "\n\rне на клетке " << x << ", " << y;
				//std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
			break;
		}
		else if (inputBufferRecord.EventType == WINDOW_BUFFER_SIZE_EVENT)
		{
			break;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
}

bool MouseInterction::isMouseOnCell(TicTacToe& game, SHORT x, SHORT y) {
	for (auto coords : game.gameGridCoords_)
	{
		if (x >= coords.Left && y >= coords.Top && x <= coords.Right && y <= coords.Bottom)
		{
			return true;
		}
	}
	return false;
}
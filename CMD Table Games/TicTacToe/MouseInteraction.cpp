#include <Windows.h>
#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include "Headers/TicTacToeGame.h"
#include "Headers/TicTacToeModules.h"
#include "Common/Button.h"

bool MouseInterction::mouseEventWaiting(TicTacToe& game, std::vector<Button>& buttons) {
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
			if (getButtonId(buttons, x, y) != -1)
			{
				int id = getButtonId(buttons, x, y);
				bool isMousePressed = mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && mer.dwEventFlags == 0;
				if(isMousePressed)
					buttons.at(id).setButtonState(Button::State::pressed);
				else
					buttons.at(id).setButtonState(Button::State::aiming);
			}
			else
			{
				for (auto& button : buttons)
				{
					if (button.getState() == Button::State::aiming)
					{
						button.setButtonState(Button::State::noInteraction);
					}
				}
			}
			if (isMouseOnCell(game, x, y) && game.gameResult_ == TicTacToe::GameResult::notDefined)
			{
				bool isMousePressed = mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && mer.dwEventFlags == 0;
				if (isMousePressed && 
					(game.getCellStatus(game.getCell(x, y)) == TicTacToe::CellStatus::focus ||
					game.getCellStatus(game.getCell(x, y)) == TicTacToe::CellStatus::empty))
				{
					if (game.stepCount_ % 2 == 0)
					{
						game.setCell(TicTacToe::CellStatus::cross, game.getCell(x, y));
						++game.stepCount_;
						return true;
					}
					else
					{
						game.setCell(TicTacToe::CellStatus::zero, game.getCell(x, y));
						++game.stepCount_;
						return true;
					}
				}
				else
				{
					if (game.focusedCellId_ != -1 && 
						game.getCellStatus(game.focusedCellId_) == TicTacToe::CellStatus::focus)
					{
						game.setCell(TicTacToe::CellStatus::empty, game.focusedCellId_);
					}
					game.focusedCellId_ = game.getCell(x, y);
					if (game.getCellStatus(game.focusedCellId_) == TicTacToe::CellStatus::empty)
					{
						game.setCell(TicTacToe::CellStatus::focus, game.focusedCellId_);
					}
				}
			}
			else
			{
				if (game.focusedCellId_ != -1 &&
					game.getCellStatus(game.focusedCellId_) == TicTacToe::CellStatus::focus)
				{
					game.setCell(TicTacToe::CellStatus::empty, game.focusedCellId_);
				}
			}
			break;
		}
		else if (inputBufferRecord.EventType == WINDOW_BUFFER_SIZE_EVENT)
		{
			game.clearScreen();
			break;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
	return false;
}

int MouseInterction::getButtonId(const std::vector<Button>& buttons, SHORT x, SHORT y) {
	for (int i{}; i < buttons.size(); ++i)
	{
		if (x >= buttons.at(i).getCoordX() && x <= (buttons.at(i).getCoordX() + buttons.at(i).getSizeX()) &&
			y >= buttons.at(i).getCoordY() && y <= (buttons.at(i).getCoordY() + buttons.at(i).getSizeY()))
		{
			return i;
		}
	}
	return -1;
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
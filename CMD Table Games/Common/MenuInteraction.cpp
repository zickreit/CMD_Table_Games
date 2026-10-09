#include <Windows.h>
#include <thread>
#include <chrono>
#include "Headers/MenuInteraction.h"
#include "Headers/ConsoleWindow.h"


bool mouseEventWaiting(ConsoleWindow& cw, std::vector<Button>&& buttons) {
	HANDLE hInput = cw.getHandleInput();
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
			for (auto& button : buttons)
			{
				if (button.isSwitchButton())
				{
					if (button.getSwitchState() == 0)
					{
						button.setButtonState(Button::State::noInteraction);
					}
					else if (button.getSwitchState() == 1)
					{
						button.setButtonState(Button::State::activated);
					}
				}
				else if (button.getState() == Button::State::aiming)
				{
					button.setButtonState(Button::State::noInteraction);
				}
			}
			if (getButtonId(buttons, x, y) != -1)
			{
				int id = getButtonId(buttons, x, y);
				bool isMousePressed = mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && mer.dwEventFlags == 0;
				if (buttons.at(id).isSwitchButton())
				{
					if (isMousePressed)
					{
						buttons.at(id).setSwitchState(1 - buttons.at(id).getSwitchState());
						buttons.at(id).setButtonState(Button::State::pressed);
					}
					else
					{
						buttons.at(id).setButtonState(Button::State::aiming);
					}
				}
				else if (buttons.at(id).getState() != Button::State::activated)
				{
					if (isMousePressed)
					{
						buttons.at(id).setButtonState(Button::State::pressed);
					}
					else
					{
						buttons.at(id).setButtonState(Button::State::aiming);
					}
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
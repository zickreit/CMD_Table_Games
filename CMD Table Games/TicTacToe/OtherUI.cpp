#include "Headers/TicTacToeModules.h"
#include "Headers/TicTacToeGame.h"

OtherUI::OtherUI() {
	buttons_.push_back(Button("Рестарт"));
	buttons_.push_back(Button("Выбрать противника", true));
	buttons_.push_back(Button("Второй игрок"));
	buttons_.push_back(Button("Бот (лёгкий)"));
	buttons_.push_back(Button("Бот (средний)"));
	buttons_.push_back(Button("Бот (сложный)"));
	buttons_.push_back(Button("Выбрать размер поля", true));
	buttons_.push_back(Button("(3 x 3)"));
	buttons_.push_back(Button("(5 x 5)"));
	buttons_.push_back(Button("(10 x 10)"));
	buttons_.push_back(Button("(15 x 15)"));
}

int OtherUI::getButtonId(short x, short y) {
	return 0;
}

void OtherUI::implementButtonAction(TicTacToe& game, int id) {
	switch (id)
	{
	case 0:
		if (buttons_.at(id).getState() != Button::State::pressed) break;
		game.setRestartRequirement(true);
		break;
	case 1:
		if (buttons_.at(1).getSwitchState() == 1)
		{
			buttons_.at(6).setSwitchState(0);
			buttons_.at(2).setButtonState(game.bot.getMode() == Bot::Modes::off ? Button::State::activated : Button::State::noInteraction);
			buttons_.at(3).setButtonState(game.bot.getMode() == Bot::Modes::easy ? Button::State::activated : Button::State::noInteraction);
			buttons_.at(4).setButtonState(game.bot.getMode() == Bot::Modes::medium ? Button::State::activated : Button::State::noInteraction);
			buttons_.at(5).setButtonState(game.bot.getMode() == Bot::Modes::hard ? Button::State::activated : Button::State::noInteraction);
		}
		else if (buttons_.at(1).getSwitchState() == 0)
		{
			buttons_.at(1).setButtonState(Button::State::noInteraction);
		}
		break;
	case 2:
		if (buttons_.at(id).getState() != Button::State::pressed) break;
		buttons_.at(1).setSwitchState(0);
		game.bot.setMode(Bot::Modes::off);
		game.scoreBot_ = 0;
		game.scorePlayer_ = 0;
		game.setRestartRequirement(true);
		buttons_.at(2).setButtonState(Button::State::noInteraction);
		break;
	case 3:
		if (buttons_.at(id).getState() != Button::State::pressed) break;
		buttons_.at(1).setSwitchState(0);
		game.bot.setMode(Bot::Modes::easy);
		game.scoreBot_ = 0;
		game.scorePlayer_ = 0;
		game.setRestartRequirement(true);
		buttons_.at(3).setButtonState(Button::State::noInteraction);
		break;
	case 4:
		if (buttons_.at(id).getState() != Button::State::pressed) break;
		buttons_.at(1).setSwitchState(0);
		game.bot.setMode(Bot::Modes::medium);
		game.scoreBot_ = 0;
		game.scorePlayer_ = 0;
		game.setRestartRequirement(true);
		buttons_.at(4).setButtonState(Button::State::noInteraction);
		break;
	case 5:
		if (buttons_.at(id).getState() != Button::State::pressed) break;
		buttons_.at(1).setSwitchState(0);
		game.bot.setMode(Bot::Modes::hard);
		game.scoreBot_ = 0;
		game.scorePlayer_ = 0;
		game.setRestartRequirement(true);
		buttons_.at(5).setButtonState(Button::State::noInteraction);
		break;
	case 6:
		if (buttons_.at(6).getSwitchState() == 1)
		{
			buttons_.at(1).setSwitchState(0);
			buttons_.at(7).setButtonState(game.gridSize_ == 3 ? Button::State::activated : Button::State::noInteraction);
			buttons_.at(8).setButtonState(game.gridSize_ == 5 ? Button::State::activated : Button::State::noInteraction);
			buttons_.at(9).setButtonState(game.gridSize_ == 10 ? Button::State::activated : Button::State::noInteraction);
			buttons_.at(10).setButtonState(game.gridSize_ == 15 ? Button::State::activated : Button::State::noInteraction);
		}
		else if (buttons_.at(6).getSwitchState() == 0)
		{
			buttons_.at(6).setButtonState(Button::State::noInteraction);
		}
		break;
	case 7:
		if (buttons_.at(id).getState() != Button::State::pressed) break;
		buttons_.at(6).setSwitchState(0);
		game.setGridSize(3);
		game.scoreBot_ = 0;
		game.scorePlayer_ = 0;
		game.setRestartRequirement(true);
		buttons_.at(7).setButtonState(Button::State::noInteraction);
		break;
	case 8:
		if (buttons_.at(id).getState() != Button::State::pressed) break;
		buttons_.at(6).setSwitchState(0);
		game.setGridSize(5);
		game.scoreBot_ = 0;
		game.scorePlayer_ = 0;
		game.setRestartRequirement(true);
		buttons_.at(8).setButtonState(Button::State::noInteraction);
		break;
	case 9:
		if (buttons_.at(id).getState() != Button::State::pressed) break;
		buttons_.at(6).setSwitchState(0);
		game.setGridSize(10);
		game.scoreBot_ = 0;
		game.scorePlayer_ = 0;
		game.setRestartRequirement(true);
		buttons_.at(9).setButtonState(Button::State::noInteraction);
		break;
	case 10:
		if (buttons_.at(id).getState() != Button::State::pressed) break;
		buttons_.at(6).setSwitchState(0);
		game.setGridSize(15);
		game.scoreBot_ = 0;
		game.scorePlayer_ = 0;
		game.setRestartRequirement(true);
		buttons_.at(10).setButtonState(Button::State::noInteraction);
		break;
	}

}

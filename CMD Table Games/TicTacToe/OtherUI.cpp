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
		break;
	case 3:
		if (buttons_.at(id).getState() != Button::State::pressed) break;
		buttons_.at(1).setSwitchState(0);
		game.bot.setMode(Bot::Modes::easy);
		game.scoreBot_ = 0;
		game.scorePlayer_ = 0;
		game.setRestartRequirement(true);
		break;
	case 4:
		if (buttons_.at(id).getState() != Button::State::pressed) break;
		buttons_.at(1).setSwitchState(0);
		game.bot.setMode(Bot::Modes::medium);
		game.scoreBot_ = 0;
		game.scorePlayer_ = 0;
		game.setRestartRequirement(true);
		break;
	case 5:
		if (buttons_.at(id).getState() != Button::State::pressed) break;
		buttons_.at(1).setSwitchState(0);
		game.bot.setMode(Bot::Modes::hard);
		game.scoreBot_ = 0;
		game.scorePlayer_ = 0;
		game.setRestartRequirement(true);
		break;
	case 6:
		if (buttons_.at(6).getSwitchState() == 1)
		{
			buttons_.at(1).setSwitchState(0);
			buttons_.at(7).setButtonState(game.bot.getMode() == Bot::Modes::off ? Button::State::activated : Button::State::noInteraction);
			buttons_.at(8).setButtonState(game.bot.getMode() == Bot::Modes::easy ? Button::State::activated : Button::State::noInteraction);
			buttons_.at(9).setButtonState(game.bot.getMode() == Bot::Modes::medium ? Button::State::activated : Button::State::noInteraction);
			buttons_.at(10).setButtonState(game.bot.getMode() == Bot::Modes::hard ? Button::State::activated : Button::State::noInteraction);
		}
		else if (buttons_.at(6).getSwitchState() == 0)
		{
			buttons_.at(6).setButtonState(Button::State::noInteraction);
		}
		break;
	}
}

#include "Headers/TicTacToeModules.h"
#include "Headers/TicTacToeGame.h"

OtherUI::OtherUI() {
	buttons_.push_back(Button("Рестарт"));
	buttons_.push_back(Button("Выбрать противника"));
	buttons_.push_back(Button("Второй игрок"));
	buttons_.push_back(Button("Бот (лёгкий)"));
	buttons_.push_back(Button("Бот (средний)"));
	buttons_.push_back(Button("Бот (сложный)"));
	buttons_.push_back(Button("Выбрать размер поля"));
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
		game.setRestartRequirement(true);
		break;
	case 1:
		buttons_.at(1).setButtonState(Button::State::notActive);
		buttons_.at(2).setButtonState(game.bot.getMode() == Bot::Modes::off ? Button::State::notActive : Button::State::noInteraction);
		buttons_.at(3).setButtonState(game.bot.getMode() == Bot::Modes::easy ? Button::State::notActive : Button::State::noInteraction);
		buttons_.at(4).setButtonState(game.bot.getMode() == Bot::Modes::medium ? Button::State::notActive : Button::State::noInteraction);
		buttons_.at(5).setButtonState(game.bot.getMode() == Bot::Modes::hard ? Button::State::notActive : Button::State::noInteraction);
		break;
	case 2:
		buttons_.at(1).setButtonState(Button::State::noInteraction);
		game.bot.setMode(Bot::Modes::off);
		game.setRestartRequirement(true);
		break;
	case 3:
		buttons_.at(1).setButtonState(Button::State::noInteraction);
		game.bot.setMode(Bot::Modes::easy);
		game.setRestartRequirement(true);
		break;
	case 4:
		buttons_.at(1).setButtonState(Button::State::noInteraction);
		game.bot.setMode(Bot::Modes::medium);
		game.setRestartRequirement(true);
		break;
	case 5:
		buttons_.at(1).setButtonState(Button::State::noInteraction);
		game.bot.setMode(Bot::Modes::hard);
		game.setRestartRequirement(true);
		break;

	}
}

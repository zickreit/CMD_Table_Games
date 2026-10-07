#include "Headers/TicTacToeModules.h"
#include "Headers/TicTacToeGame.h"

OtherUI::OtherUI() {
	buttons_.push_back(Button("Начать заново"));
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
	}
}

#include <random>
#include <thread>
#include <chrono>
#include "Headers/TicTacToeModules.h"
#include "Headers/TicTacToeGame.h"

void Bot::makeMove(TicTacToe& game) {
	if (game.gameResult_ != TicTacToe::GameResult::notDefined) return;
	auto cellStatus = game.stepCount_ % 2 == 0 ? TicTacToe::CellStatus::cross : TicTacToe::CellStatus::zero;
	game.setCell(cellStatus, getCellIdEasyMode(game));
	++game.stepCount_;
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

int Bot::getCellIdEasyMode(TicTacToe& game) {
	static std::random_device rd;
	static std::mt19937 mt(rd());
	std::uniform_int_distribution<int> distrib(0, game.gridSize_ * game.gridSize_ - 1);
	int randomId = distrib(mt);
	while (game.getCellStatus(randomId) != TicTacToe::CellStatus::empty &&
		  game.getCellStatus(randomId) != TicTacToe::CellStatus::focus)
	{
		randomId = distrib(mt);
	}
	return randomId;
}
int Bot::getCellIdMediumMode(TicTacToe& game) {
	return 0;
}
int Bot::getCellIdHardMode(TicTacToe& game) {
	return 0;
}
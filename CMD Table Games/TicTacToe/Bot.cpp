#include <random>
#include <thread>
#include <chrono>
#include <vector>
#include <stdexcept>
#include "Headers/TicTacToeModules.h"
#include "Headers/TicTacToeGame.h"

void Bot::makeMove(TicTacToe& game) {
	if (game.gameResult_ != TicTacToe::GameResult::notDefined) return;
	auto cellStatus = game.stepCount_ % 2 == 0 ? TicTacToe::CellStatus::cross : TicTacToe::CellStatus::zero;
	game.setCell(cellStatus, getCellIdHardMode(game));
	++game.stepCount_;
	//std::this_thread::sleep_for(std::chrono::seconds(1));
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
	// Цель: найти самый безпроигрышный ход
	// Задачи:
	//	- сделать главное хранилище счёта каждой клетки
	//	- подсчёт счёта для каждой клетки совершать таким образом:
	//	 * создаём массив, где храним счёт каждой комбинации с клеткой родителем на N ходов вперёд
	//	 * для каждой комбинации делаем N количество случайных симуляций игры, добавляем (1, 0, -1) к счёту комбинации
	//   * делим получившийся счёт на количество пройденных симуляций
	//	 * находим комбинацию с большим счётом
	//	 * итоговый счёт отдаём клетке родителю
	//	- находим клетку с большим счётом и выводим её
	int simNum				= 200;
	int mainCellsNum		= game.gridSize_ * game.gridSize_;
	int completedMoves		= game.stepCount_;
	int forwardMovesNum		= (std::min)(3, mainCellsNum - completedMoves - 1);
	int possibleCombsNum	= 1;
	for (int possibleCells = mainCellsNum - completedMoves - 1; possibleCells > mainCellsNum - completedMoves  - 1 - forwardMovesNum; --possibleCells)
	{
		possibleCombsNum *= possibleCells;
	}
	std::vector<int> mainCellsScore(mainCellsNum - game.stepCount_);
	for (int cellId{}; cellId < mainCellsNum; ++cellId)
	{
		if (game.getCellStatus(cellId) == TicTacToe::CellStatus::cross ||
			game.getCellStatus(cellId) == TicTacToe::CellStatus::zero) continue;
		std::vector<CombinationInfo> combsScore(possibleCombsNum);
		std::vector<int> combCellsId(forwardMovesNum + 1);
		combCellsId[0] = cellId;
		int extraCellId{};
		for (int step{1}; step < forwardMovesNum + 1; ++step)
		{
			while (game.getCellStatus(extraCellId) == TicTacToe::CellStatus::cross ||
				   game.getCellStatus(extraCellId) == TicTacToe::CellStatus::zero ||
				   extraCellId == cellId)
			{
				++extraCellId;
			}
			combCellsId[step] = extraCellId++;
		}
		bool isNeedBreak{};
		for(auto& comb : combsScore)
		{
			comb = CombinationInfo(combCellsId);
			int step = forwardMovesNum;
			++combCellsId[step];
			bool isCombFound{};
			while(!isCombFound)
			{
				isCombFound = true;
				while (combCellsId[step] >= mainCellsNum)
				{
					combCellsId[step] = 0;
					if (step - 1 == 0)
					{
						isNeedBreak = true;
						break;
					}
					--step;
					++combCellsId[step];
					isCombFound = false;
				}
				while (game.getCellStatus(combCellsId[step]) == TicTacToe::CellStatus::cross ||
					   game.getCellStatus(combCellsId[step]) == TicTacToe::CellStatus::zero ||
					   combCellsId[step] == cellId)
				{
					++combCellsId[step];
					isCombFound = false;
				}
				
				if (isNeedBreak) break;
			}
			if (isNeedBreak) break;
		}
		for (auto& comb : combsScore)
		{
			for (int simCount{}; simCount < simNum; ++simCount)
			{

			}
		}
	}
	return 0;
}
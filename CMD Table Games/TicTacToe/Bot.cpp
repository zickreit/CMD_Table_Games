#include <random>
#include <thread>
#include <chrono>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include "Headers/TicTacToeBot.h"

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
	int forwardMovesNum		= 3;

	int mainCellsNum		= game.gridSize_ * game.gridSize_;
	int completedMoves		= game.stepCount_;
	int forwardMovesNumReal	= (std::min)(forwardMovesNum, mainCellsNum - completedMoves - 1);
	int possibleCombsNum	= 1;
	for (int possibleCells = mainCellsNum - completedMoves - 1; possibleCells > mainCellsNum - completedMoves  - 1 - forwardMovesNumReal; --possibleCells)
	{
		possibleCombsNum *= possibleCells;
	}
	std::vector<int> mainCellsScore(mainCellsNum, 0);
	for (int cellId{}; cellId < mainCellsNum; ++cellId)
	{
		if (game.getCellStatus(cellId) == TicTacToe::CellStatus::cross ||
			game.getCellStatus(cellId) == TicTacToe::CellStatus::zero) continue;
		std::vector<CombinationInfo> combsScore(possibleCombsNum);
		std::vector<int> combCellsId(forwardMovesNumReal + 1);
		combCellsId[0] = cellId;
		bool isNeedBreak{};
		for (auto& comb : combsScore)
		{
			bool isCombFound{};
			while (!isCombFound)
			{
				isCombFound = true;
				for (int tempStep = forwardMovesNumReal; tempStep > 1; --tempStep)
				{
					while (combCellsId[tempStep] >= mainCellsNum)
					{
						combCellsId[tempStep] = 0;
						if (tempStep - 1 == 0)
						{
							isNeedBreak = true;
							break;
						}
						++combCellsId[tempStep - 1];
						isCombFound = false;
					}
				}
				if (isNeedBreak) break;
				for (int tempStep = 1; tempStep <= forwardMovesNumReal && isCombFound; ++tempStep)
				{
					while (combCellsId[tempStep] < mainCellsNum - 1 &&
						(game.getCellStatus(combCellsId[tempStep]) == TicTacToe::CellStatus::cross ||
						game.getCellStatus(combCellsId[tempStep]) == TicTacToe::CellStatus::zero))
					{
						++combCellsId[tempStep];
						isCombFound = false;
					}
					for (int tempId{}; tempId <= forwardMovesNumReal; ++tempId)
					{
						if (combCellsId[tempId] == combCellsId[tempStep] && tempId != tempStep)
						{
							if(tempStep < tempId)
								++combCellsId[tempId];
							else
								++combCellsId[tempStep];
							isCombFound = false;
						}
					}
				}
			}
			if (isNeedBreak) break;
			comb = CombinationInfo(combCellsId);
			++combCellsId[forwardMovesNumReal];
		}
		if (isNeedBreak) break;

		static std::random_device rd;
		static std::mt19937 mt(rd());
		std::uniform_int_distribution<int> distrib(0, game.gridSize_ * game.gridSize_ - 1);

		for (auto& comb : combsScore)
		{
			for (int simCount{}; simCount < simNum; ++simCount)
			{
				bool isNeedContinue{};
				simSteps_ = game.stepCount_;
				simGridStats_ = game.gameGridStats_;
				for (auto& simCell : comb.cellsId)
				{
					if (simSteps_ % 2 == 0)
					{
						simGridStats_[simCell] = TicTacToe::CellStatus::cross;
					}
					else
					{
						simGridStats_[simCell] = TicTacToe::CellStatus::zero;
					}
					++simSteps_;
					auto gameResult = game.checkGameResult(true);
					if (gameResult == TicTacToe::GameResult::win)
					{
						--comb.score;
						isNeedContinue = true;
						++comb.movesNum;
						break;
					}
					else if (gameResult == TicTacToe::GameResult::lose)
					{
						++comb.score;
						isNeedContinue = true;
						++comb.movesNum;
						break;
					}
					else if (gameResult == TicTacToe::GameResult::draw)
					{
						isNeedContinue = true;
						++comb.movesNum;
						break;
					}
				}
				if (isNeedContinue) continue;
				while (simSteps_ < mainCellsNum)
				{
					int randCellId = distrib(mt);
					while (getSimCellStatus(randCellId) != TicTacToe::CellStatus::empty &&
						   getSimCellStatus(randCellId) != TicTacToe::CellStatus::focus)
					{
						randCellId = distrib(mt);
					}
					if (simSteps_ % 2 == 0)
					{
						simGridStats_[randCellId] = TicTacToe::CellStatus::cross;
					}
					else
					{
						simGridStats_[randCellId] = TicTacToe::CellStatus::zero;
					}
					++simSteps_;
					auto gameResult = game.checkGameResult(true);
					if (gameResult == TicTacToe::GameResult::win)
					{
						--comb.score;
						++comb.movesNum;
						break;
					}
					else if (gameResult == TicTacToe::GameResult::lose)
					{
						++comb.score;
						++comb.movesNum;
						break;
					}
					else if (gameResult == TicTacToe::GameResult::draw)
					{
						++comb.movesNum;
						break;
					}
				}
			}
		}

		for (auto& comb : combsScore)
		{
			if (mainCellsScore[cellId] < comb.score)
			{
				mainCellsScore[cellId] = comb.score;
			}
		}
	}
	
	auto maxIt = std::ranges::max_element(mainCellsScore);
	auto finalCell = std::distance(mainCellsScore.begin(), maxIt);

	return finalCell;
}

TicTacToe::CellStatus Bot::getSimCellStatus(int id) {
	if (id < 0 || id >= simGridStats_.size())
	{
		throw std::runtime_error("Критическая ошибка: Неверный ID в вызове getSimCellStatus!\n");
	}
	return simGridStats_.at(id);
}

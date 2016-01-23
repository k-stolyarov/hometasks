#include "bonus.h"

bonus::bonus()
	: minesweeper()
{
}

bonus::bonus(int col, int row, int numOfMines)
	: minesweeper(col, row, numOfMines)
{
}

int bonus::saveGame(std::string path)
{
	return 0;
}

int bonus::loadGame(std::string path)
{
	return 0;
}
int bonus::saveStatistics(std::string path)
{
	return 0;
}

int bonus::loadStatistics(std::string path)
{
	return 0;
}

int bonus::getWins()
{
	return wins;
}

void bonus::setWins(int in_wins)
{
	wins = in_wins;
}
int bonus::getLoss()
{
	return loss;
}

void bonus::setLoss(int in_loss)
{
	loss = in_loss;
}

double bonus::getRatio()
{
	return static_cast<double>(wins) / loss;
}

int bonus::getWinStreak()
{
	return winStreak;
}

void bonus::setWinStreak(int win_streak)
{
	winStreak = win_streak;
}

int bonus::getLongestWinStreak()
{
	return longestWinStreak;
}
void bonus::setLongestWinStreak(int win_streak)
{
	longestWinStreak = win_streak;
}

void bonus::initialMineField(int fpX, int fpY)
{
	// \todo implement;
}

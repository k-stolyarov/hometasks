#include "bonus.h"
#include <fstream>
#include <string>
#include <sstream>

namespace
{

const char * wins_string = "wins";
const char * loss_string = "loss";
const char * current_streak = "current_streak";
const char * longest_streak = "longest_streak";

// reads value from a string to  given variable if line prefix matches.
void read_if_match(const std::string & line, const std::string &prefix, int & destination)
{
	if (line.find(prefix) == 0)
	{
		stringstream ss(line.substr(prefix.size()));
		char delim;
		ss >> delim >> destination;
	}
}

}

bonus::bonus()
	: minesweeper()
	, wins(0)
	, loss(0)
	, winStreak(0)
	, longestWinStreak(0)
{
}

bonus::bonus(int col, int row, int numOfMines)
	: minesweeper(col, row, numOfMines)
	, wins(0)
	, loss(0)
	, winStreak(0)
	, longestWinStreak(0)
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
	ofstream fs(path.c_str());
	fs << wins_string << ": " << wins << "\n";
	fs << loss_string << ": " << loss << "\n";
	fs << current_streak << ": " << winStreak << "\n";
	fs << longest_streak << ": " << longestWinStreak << "\n";
	return 0;
}

int bonus::loadStatistics(std::string path)
{
	ifstream fs(path.c_str());
	while (fs.good())
	{
		std::string line;
		getline(fs, line);
		parse_line(line);
	}
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

bool bonus::is_tile_allowed_to_place_mine(int fpX, int fpY, int tile_x, int tile_y) const
{
	// do not allow to place mine at position of first turn.
	return fpX != tile_x || fpY != tile_y;
}

void bonus::parse_line(const std::string &line)
{
	read_if_match(line, wins_string, wins);
	read_if_match(line, loss_string, loss);
	read_if_match(line, current_streak, winStreak);
	read_if_match(line, longest_streak, longestWinStreak);
}

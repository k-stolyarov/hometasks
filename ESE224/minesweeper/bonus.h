#include <string>
#include "minesweeper.h"


#ifndef bonus_H
#define	bonus_H

class bonus : public minesweeper {
public:
	bonus();
	bonus(int col, int row, int numOfMines);  //Constructor given board dimensions and number of mines

	int saveGame(std::string path);        //Save minesweeper object state to file
	int loadGame(std::string path);        //Load minesweeper object state from file
	int saveStatistics(std::string path);  //Save overall game statistics to file
	int loadStatistics(std::string path);  //Load overall game statistics from file
	int getWins();                         //Returns # of wins
	void setWins(int wins);                        //Modify # of wins
	int getLoss();                         //Returns # of losses
	void setLoss(int loss);                        //Modify # of losses
	double getRatio();                     //Returns Win/loss Ratio
	int getWinStreak();                    //Returns current Win Streak (consecutive wins)
	void setWinStreak(int wins_streak);                   //Modifies current Win Streak # (consecutive wins)
	int getLongestWinStreak();             //Returns longest Win Streak (largest win streak seen)
	void setLongestWinStreak(int wins_streak);            //Modifies longest Win Streak (largest win streak seen)


protected:
	//Overrides minesweeper::is_tile_allowed_to_place_mine to change behaviour of mines placement.
	virtual bool is_tile_allowed_to_place_mine(int fpX, int fpY, int tile_x, int tile_y) const;
	
private:
	// Parse a single line from input file and save value  to one of fields.
	void parse_line(const std::string & line);

	int wins;                               // # of total wins
	int loss;                               // # of total losses
	int winStreak;                          // Current win streak count
	int longestWinStreak;                   // Longest win streak count
};

#endif	/* BONUS_H */
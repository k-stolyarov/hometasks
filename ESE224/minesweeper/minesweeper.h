#ifndef MINESWEEPER_H_
#define MINESWEEPER_H_

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <stdlib.h>
#include <ctime>
#include <string>

using namespace std;

// Extended support of fetching "isMarked" flag for a tile. For better UI.
#define MINESWEEPER_IS_MARKED_SUPPORTED
#define MINESWEEPER_DEBUG_MODE_SUPPORTED

class minesweeper {
private:
	struct BoardTile
	{
		BoardTile();

		// Is tile visible
		bool hidden;
		// Do tile contain a mine
		bool has_mine;
		// Is tile marked as potential mine
		bool is_marked;
		// Amount of surrounding mines (if tile contain mine value is -1)
		int surrounding_mines_count;
	};
	enum GameStatus
	{
		LOSS = -1,
		ONGOING = 0,
		WIN = 1
	};

private:
	int columns_;                                  //number of columns on game board (X))
	int rows_;                                  //number of rows on game board(Y)
	int mines_;                                //number of mines placed on game board
	GameStatus game_status_;                                 //end game condition tracker (-1 loss, 0 ongoing, 1 win)
	vector<vector<BoardTile> > field_;           //actual representation of game board

	int randomPick(int num);						// return number in range 0.... num-1
	void clearField();								// clear minefield and set it's size to specified value.
	void calculateSurrounding(int x, int y);                    //Updates board tiles by adding 1 to tiles surrounding mine except when adjacent tile is mine
	void onlyMines();								// Update game_status with ONGOING or WIN values.
	void unmask(int x, int y);                  //Actual function to reveal blank tile. Makes recursive calls for 0 value tiles
protected:
	// Check if tile with coordinates(tile_x, tile_y) is allowed to place mine.
	virtual bool is_tile_allowed_to_place_mine(int fpX, int fpY, int tile_x, int tile_y) const;
public:

	minesweeper();                                  //Default constructor
	virtual ~minesweeper();                         //Destructor
	minesweeper(int col, int row, int numOfMines);  //Constructor given board dimensions and number of mines

	int getColNum();                                //Return # of columns for game board
	int getRowNum();                                //Return # of rows for game board
	int getMinesNum();                              //Return total # of mines on game board
	int endGame();                                  //Return current end game status
	virtual void initialMineField(int fpX, int fpY);        //Initialize game board given file path of initial mine placement w/o checking for 1st turn game over
	void initialMineField(string path);             //Initialize game board given first revealed tile
	bool isRevealed(int x, int y);                  //Checks if tile has been already revealed
	void revealLocation(int x, int y);              //Reveals selected tile. Selected tile should return true on subsequent isRevealed calls, the left click action
#ifdef MINESWEEPER_IS_MARKED_SUPPORTED
	bool isMarked(int x, int y) const;				//Checks if tile has been already marked
#endif // #ifdef MINESWEEPER_IS_MARKED_SUPPORTED
	void markLocation(int x, int y);                // mark a cell as potential mine, the right click action	
	int valueOf(int x, int y);                      //Returns tile value (# of surrounding mines if not mine)
#ifdef MINESWEEPER_DEBUG_MODE_SUPPORTED
	int debugModeValueOf(int x, int y);                      //Returns tile value (# of surrounding mines if not mine)
#endif // MINESWEEPER_DEBUG_MODE_SUPPORTED
};


#endif /* MINESWEEPER_H_ */

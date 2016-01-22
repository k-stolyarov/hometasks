#include "minesweeper.h"

using namespace std;

minesweeper::minesweeper() {
	// TODO - default two dimension array is 9 X 9 with 10 mines
}

minesweeper::minesweeper(int col, int row, int numOfMines) {
	// TODO Auto-generated constructor stub
	// TODO - two dimension gameboard size col x num with numOfMines mines
}

minesweeper::~minesweeper() {
	// TODO Auto-generated destructor stub
}

/**
 * Returns int representing number of rows of current playing field.
 *
 * @return      Number of rows on playing field
 * */
int minesweeper::getRowNum()
{
	return 0;
}

/**
 * Returns int representing number of columns of current playing field.
 *
 * @return      Number of rows on playing field
 * */
int minesweeper::getColNum()
{
	return 0;
}
/**
 * Returns int representing number of mines on current playing field.
 * Includes both hidden and revealed mines.
 *
 * @return      Number of rows on playing field
 * */
int minesweeper::getMinesNum()
{
	return 0;
}

/**
 * Returns int randomly generated between 0 and num
 *
 * @param   num Upper limit of randomly generated number
 * @return      Number of rows on playing field
 * @see         initialMineField()
 * */
int minesweeper::randomPick(int num)
{
	return rand() % num;
}

/**
 * Generates mine field after accepting player's first turn.
 * Does not have to avoid first turn game over. 
 *
 * @param   fpX X-coordinate of first pick
 * @param   fpY Y-coordinate of first pick
 * @see     calculateSurrounding()
 * @see     randomPick()
 * */
void minesweeper::initialMineField(int fpX, int fpY) {
	//Generate our map and mask
	//TODO - generate all mines randomly
	//surrounding tile values should be updated to reflect presence of adjacent mine
}

/**
 * Generates mine field based on file. This option
 * does not have to check the user's first turn for 1-turn game over.
 *
 * @param   path to load MineField from
 * */
void minesweeper::initialMineField(string path) { 
	//TODO - load mine field from path
	//Is not concerned with user's first tile
}

/**
 * Generates numbers for surrounding tiles of mines. The only
 * tiles with numbers are those surrounding mines; these tiles are
 * updated as mines are generated.

 *
 * @param   row Row number of generated mine
 * @param   col Column number of generated mine
 * @see     initialMineField()
 * */
void minesweeper::calculateSurrounding(int row, int col) {
	//TODO - should update surrounding tiles to reflect
	//presence of adjacent mine
}

/**
 * Updates bitField with user selection of revealed location.
 * Reveals current location and immediately checks mineField
 * for mine. Recursively calls helper function unmask for blank
 * tiles. 
 *
 * @param   row Row number of user selected tile
 * @param   col Column number of user selected tile
 * @see         unmask();
 * */
void minesweeper::revealLocation(int x, int y) {
	//TODO - update the bitField to reflect the user's
	//tile selection. Should rely on unmask to do actual
	//reveal operation.
}

/**
 * Allow the user to mark a cell as a potential mine. Marking an already
 * marked cell will remove the mark for that cell
 *
 * @param x column number of the cell selected
 * @param y row number of the cell selected
 */
void minesweeper::markLocation(int x, int y) {
    // TODO - update the display for the selected cell, change it
    // to marked if it's not marked, or to unmarked if it's already marked
}

/**
 * Checks end game status (int end). End -1 is loss condition.
 * Also checks onlyMines() for a win condition. onlyMines will
 * update the end game status and endGame should return this value.
 *
 * @return      end game status (-1 loss, 0 ongoing, 1 win)
 * @see         onlyMines();
 * @see		revealLocation();
 * */
int minesweeper::endGame() {
	//TODO - return current end game status.
	//Calling this method should only update int end with
	//win or ongoing condition. revealLocation should
	//update if there is loss condition.
	return 0;
}

/**
 * Checks end game status (int end). End 1 is win condition;
 * end 0 is ongoing. onlyMines will only update end with these
 * two conditions. onlyMines will check the entire playing field
 * (does not rely on numMines or any internal counter). 
 *
 * @see         endGame();
 * */
void minesweeper::onlyMines() {
	//TODO - check for win condition, otherwise ongoing
}

/**
 * Checks if the selected position should be visible
 *
 * @param   row Row number of user selected tile
 * @param   col Column number of user selected tile
 * @see         valueOf();
 * */
bool minesweeper::isRevealed(int x, int y) {
	//TODO - check if a user has revealed a specific tile
	return false;
}

/**
 * Checks if the value of selected tile. isRevealed
 * should be called before this for correct gameplay. 
 * 
 * @param   row Row number of user selected tile
 * @param   col Column number of user selected tile
 * @see         isRevealed();
 * */
int minesweeper::valueOf(int x, int y) {
	//TODO - returns the value of specific tile.
	//should only be called if tile isRevealed.
	return 0;
}

/**
 * Reveals surrounding tiles. Should only be called if
 * user selected tile was not mine or had no surrounding
 * mines. Will recursively call itself to reveal all
 * adjacent blank tiles.
 *
 * @param   row Row number of user selected tile
 * @param   col Column number of user selected tile
 * @see         revealLocation();
 * */
void minesweeper::unmask(int row,int col) {
	//TODO - reveal the tile here.
	//This method should reveal surrounding tiles
	//if the tile revealed had a value of 0
}

#include "minesweeper.h"
#include <fstream>

using namespace std;

minesweeper::BoardTile::BoardTile()
	: hidden(true)
	, has_mine(false)
	, is_marked(false)
	, surrounding_mines_count(0)
{
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

void minesweeper::clearField()
{
	field_.resize(rows_);
	for (int i = 0; i < rows_; ++i)
	{
		field_[i].resize(columns_);
		for (int j = 0; j < columns_; ++j)
		{
			field_[i][j] = BoardTile();
		}
	}
	game_status_ = ONGOING;
}

/**
* Generates numbers for surrounding tiles of mines. The only
* tiles with numbers are those surrounding mines; these tiles are
* updated as mines are generated.

*
* @param   x Column number of generated mine
* @param   y Row number of generated mine
* @see     initialMineField()
* */
void minesweeper::calculateSurrounding(int x, int y) {
	field_[y][x].surrounding_mines_count = -1;
	
	// iterate over 3x3 tiles and increase surrounding mines count.
	for (int r = max(0, y - 1); r < min(rows_, y + 1); ++r)
	{
		for (int c = max(0, x - 1); c < min(columns_, x + 1); ++c)
		{
			if (r != y && c != x)
			{
				++field_[r][c].surrounding_mines_count;
			}
		}
	}
}

/**
* Reveals surrounding tiles. Should only be called if
* user selected tile was not mine or had no surrounding
* mines. Will recursively call itself to reveal all
* adjacent blank tiles.
*
* @param   x Column number of user selected tile
* @param   y Row number of user selected tile
* @see         revealLocation();
* */
void minesweeper::unmask(int x, int y) {
	if (field_[y][x].has_mine)
	{
		throw std::logic_error("Logic error: unmask cannot be called for a tile with a mine.");
	}
	field_[y][x].hidden = false;
	if (0 == field_[y][x].surrounding_mines_count)
	{
		for (int r = max(0, y - 1); r < min(rows_, y + 1); ++r)
		{
			for (int c = max(0, x - 1); c < min(columns_, x + 1); ++c)
			{
				if (r != y && c != x)
				{
					unmask(c, r);
				}
			}
		}
	}
}

minesweeper::minesweeper()
	: minesweeper(9, 9, 10)
{
}

minesweeper::minesweeper(int col, int row, int numOfMines)
	: rows_(row)
	, columns_(col)
	, mines_(numOfMines)
{
}

minesweeper::~minesweeper() {
}

/**
 * Returns int representing number of rows of current playing field.
 *
 * @return      Number of rows on playing field
 * */
int minesweeper::getRowNum()
{
	return rows_;
}

/**
 * Returns int representing number of columns of current playing field.
 *
 * @return      Number of rows on playing field
 * */
int minesweeper::getColNum()
{
	return columns_;
}
/**
 * Returns int representing number of mines on current playing field.
 * Includes both hidden and revealed mines.
 *
 * @return      Number of rows on playing field
 * */
int minesweeper::getMinesNum()
{
	return mines_;
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
void minesweeper::initialMineField(const int fpX, const int fpY) {
	std::vector<std::pair<int, int>> tiles;
	tiles.reserve(rows_ * columns_);

	for (int i = 0; i < rows_; ++i)
	{
		for (int j = 0; j < columns_; ++j)
		{
			tiles.push_back(std::make_pair(i, j));
		}
	}
	// randomly shuffle possible mines positions
	for (int i = 0; i < static_cast<int>(tiles.size()); ++i)
	{
		swap(tiles[randomPick(tiles.size())], tiles[randomPick(tiles.size())]);
	}

	// Place mines at first @mines_ positions.
	clearField();
	for (int i = 0; i < mines_; ++i)
	{
		const int row = tiles[i].first;
		const int column = tiles[i].second;
		field_[row][column].has_mine = true;
		calculateSurrounding(column, row);
	}
}

/**
 * Generates mine field based on file. This option
 * does not have to check the user's first turn for 1-turn game over.
 *
 * @param   path to load MineField from
 * */
void minesweeper::initialMineField(string path) { 
	ifstream fs(path.c_str());
	fs >> rows_ >> columns_ >> mines_;
	clearField();
	for (int i = 0; i < mines_; ++i)
	{
		int r, c;
		char open;
		char close;
		fs >> open >> r >> c >> close;
		field_[r][c].has_mine = true;
		calculateSurrounding(c, r);
	}
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
	if (field_[y][x].has_mine)
	{
		// We stepped into a mine. BOOM!
		game_status_ = LOSS;
		return;
	}
	unmask(x, y);
}

/**
 * Allow the user to mark a cell as a potential mine. Marking an already
 * marked cell will remove the mark for that cell
 *
 * @param x column number of the cell selected
 * @param y row number of the cell selected
 */
void minesweeper::markLocation(int x, int y) {
	field_[y][x].is_marked = !field_[y][x].is_marked;
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
	if (game_status_ != LOSS)
	{
		onlyMines();
	}
	return game_status_;
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
	game_status_ = WIN;
	// check that all free-of-mines cells are opened
	for (int r = 0; r < rows_; ++r)
	{
		for (int c = 0; c < columns_; ++c)
		{
			if (!field_[r][c].has_mine && !field_[r][c].hidden)
			{
				// tile without mine is not opened. Game is not finished.
				game_status_ = ONGOING;
				return;
			}
		}
	}
}

/**
 * Checks if the selected position should be visible
 *
 * @param   row Row number of user selected tile
 * @param   col Column number of user selected tile
 * @see         valueOf();
 * */
bool minesweeper::isRevealed(int x, int y) {
	
	return !field_[y][x].hidden;
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
	if (field_[y][x].hidden)
	{
		throw std::logic_error("According to game logic reveal is required before getting tile value.");
	}
	return field_[y][x].surrounding_mines_count;
}


#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdexcept>
#include "minesweeper.h"
#include "bonus.h"

#include "clear_terminal_window.h"
#include "get_input_char.h"
#include "text_coloring.h"

using namespace std;

namespace
{
	const char * statistics_file_name = "minesweeper.stats";
	const int min_rows = 5;
	const int min_columns = 5;
	const int max_rows = 40;
	const int max_columns = 40;

	// Position of the game cursor.
	struct CursorPosition
	{
		int x;
		int y;
	};

	// Prints and of the game message and ask if one more game is required
	bool play_once_again(const char * end_game_message);
	// Check and return true if game action is known
	bool is_game_action_key_known(char action);
	// process game action input from a user: load saved game, move cursor, or reveal/mark tile.
	// return true if one more action processing is required.
	bool process_game_action(char action, bonus & ms, bool & game_in_progress, bool & display_minefield, CursorPosition & cursor);
	// print helper messages with allowed action for game playing.
	void print_play_game_helper(bool game_in_progress);
	// get character to be displayed for a specific tile.
	std::string get_tile_char(bonus & ms, int x, int y);
	// Display game boeard on the screen.
	void print_game_board(bonus & ms, const CursorPosition & cursor, bool display_minefield);

	void playTime(bonus& play);
	// Display statistics on the screen and wait until user exits it.
	void viewStatistics(bonus & ms);
	// Prints a message on the screen with warning that entered action is unknown;
	void print_unknown_action_error_message(const char action);
	// display initial actions helper on the screen.
	void print_initial_actions();
	// process user action input.
	// @return true if one more main loop iteration is required
	bool process_action_input(char action, bonus &ms);
	// Check if action key is valid and can be processed correctly.
	bool is_action_key_known(char action);
	// Print good-bye message on the screen.
	void print_good_bye_message();
} // end of anonymous namespace

int main() {

	/* main GUI loop. You should query the user for actions such 
     * as starting a game, viewing statistics, or quitting the program. You should
     * handle user input either succinctly or by making a call to a helper method
     * to perform the desired operations.
     */
	char action = 0;
	bool unknown_action_input = false;
	bonus ms;
	ms.loadStatistics(statistics_file_name);

	while (1) {
		clear_terminal_window();
		if (unknown_action_input)
		{
			print_unknown_action_error_message(action);
		}
		print_initial_actions();

		action =  get_input_char();
		if (!is_action_key_known(action))
		{
			// we do not need to process actions that are unknown
			unknown_action_input = true;
			continue;
		}

		unknown_action_input = false;
		if (!process_action_input(action, ms))
		{
			break;
		}
	}
	clear_terminal_window();
	print_good_bye_message();
	return 0;
}

namespace
{


const char play_once_again_key = 'y';
bool play_once_again(const char * end_game_message)
{
	printf("Game is over. %s%s%s\n", BOLD_RED_TEXT, end_game_message, NORMAL_TEXT);
	printf("Press '%s%c%s' or any other key to return to main menu.\n", BOLD_BRIGHT_RED_TEXT, play_once_again_key, NORMAL_TEXT);
	const char action = get_input_char();
	return action == play_once_again_key;
}

const char finish_game_action_key = 'q';
const char load_saved_game_action_key = 'l';
const char save_game_action_key = 'k';
const char start_new_game_action_key = 'n';
const char move_cursor_left_action = 'a';
const char move_cursor_right_action = 'd';
const char move_cursor_up_action = 'w';
const char move_cursor_down_action = 's';
const char mark_tile_action_key = '?';
const char open_tile_action_key = ' ';
const char switch_debug_mode_action_key = '~';

bool is_game_action_key_known(const char action)
{
	return action == finish_game_action_key
		|| action == load_saved_game_action_key
		|| action == save_game_action_key
		|| action == start_new_game_action_key
		|| action == move_cursor_left_action
		|| action == move_cursor_right_action
		|| action == move_cursor_up_action
		|| action == move_cursor_down_action
		|| action == mark_tile_action_key
		|| action == open_tile_action_key
		|| action == switch_debug_mode_action_key;
}

bool process_game_action(
	const char action,
	bonus & ms,
	bool & game_in_progress,
	bool & display_minefield,
	CursorPosition & cursor)
{
	switch (action)
	{
	case finish_game_action_key:
	{
		if (game_in_progress)
		{
			ms.setWinStreak(0);
			ms.setLoss(ms.getLoss() + 1);
			ms.saveStatistics(statistics_file_name);
			game_in_progress = false;
		}
		return false;
	}
	case load_saved_game_action_key:
	{
		if (game_in_progress)
		{
			ms.setWinStreak(0);
			ms.setLoss(ms.getLoss() + 1);
			ms.saveStatistics(statistics_file_name);
			game_in_progress = false;
		}

		printf("Enter file name with saved game:\n");
		char buf[1024];
		scanf("%s", buf);
		ms.loadGame(buf);
		cursor.x = cursor.y = 0;
		game_in_progress = true;
		break;
	}
	case save_game_action_key:
	{
		printf("Enter file name to save the game:\n");
		char buf[1024];
		scanf("%s", buf);
		ms.saveGame(buf);
		break;
	}
	case start_new_game_action_key:
	{
		if (game_in_progress)
		{
			ms.setWinStreak(0);
			ms.setLoss(ms.getLoss() + 1);
			ms.saveStatistics(statistics_file_name);
			game_in_progress = false;
		}

		int columns = 10;
		int rows = 10;
		int numberOfMines = 10;
		
		printf("Enter amount of rows:\n");
		scanf("%d", & rows);
		printf("Enter amount of columnts:\n");
		scanf("%d", &columns);
		printf("Enter amount of mines:\n");
		scanf("%d", &numberOfMines);

		rows = std::min(max_rows, std::max(rows, min_rows));
		columns = std::min(max_columns, std::max(columns, min_columns));
		numberOfMines = std::min(rows * columns - 1, std::max(1, numberOfMines));

		ms = bonus(columns, rows, numberOfMines);
		ms.loadStatistics(statistics_file_name);
		cursor.x = cursor.y = 0;
		break;
	}
	case move_cursor_left_action:
		cursor.x = std::max(0, cursor.x - 1);
		break;
	case move_cursor_right_action:
		cursor.x = std::min(ms.getColNum() - 1, cursor.x + 1);
		break;
	case move_cursor_up_action:
		cursor.y = std::max(0, cursor.y - 1);
		break;
	case move_cursor_down_action:
		cursor.y = std::min(ms.getRowNum() - 1, cursor.y + 1);
		break;
	case mark_tile_action_key:
		if (game_in_progress)
		{
			ms.markLocation(cursor.x, cursor.y);
		}
		break;
	case open_tile_action_key:
		if (!game_in_progress)
		{
			// that is first turn, field initialization required.
			ms.initialMineField(cursor.x, cursor.y);
		}
		ms.revealLocation(cursor.x, cursor.y);
		game_in_progress = true;
		break;
	case switch_debug_mode_action_key:
		display_minefield = !display_minefield;
		break;
	}
	return true;
}

void print_play_game_helper(const bool game_in_progress)
{
	printf("To quit current game press '%s%c%s'.", BOLD_BRIGHT_RED_TEXT, finish_game_action_key, NORMAL_TEXT);
	if (game_in_progress)
	{
		printf(" %sNote, current game will be lost.%s", BOLD_YELLOW_TEXT, NORMAL_TEXT);
	}
	printf("\n");

	printf("To load saved game press '%s%c%s'.", BOLD_BRIGHT_RED_TEXT, load_saved_game_action_key, NORMAL_TEXT);
	if (game_in_progress)
	{
		printf(" %sNote, current game will be lost.%s", BOLD_YELLOW_TEXT, NORMAL_TEXT);
	}
	printf("\n");
	printf("To save game press '%s%c%s'.\n", BOLD_BRIGHT_RED_TEXT, save_game_action_key, NORMAL_TEXT);
	printf("To start new game press '%s%c%s'.", BOLD_BRIGHT_RED_TEXT, start_new_game_action_key, NORMAL_TEXT);
	if (game_in_progress)
	{
		printf(" %sNote, current game will be lost.%s", BOLD_YELLOW_TEXT, NORMAL_TEXT);
	}
	printf("\n");
	printf("To reveal the tile '%s%c%s'.\n", BOLD_BRIGHT_RED_TEXT, open_tile_action_key, NORMAL_TEXT);
	printf("To mark the tile '%s%c%s'.\n", BOLD_BRIGHT_RED_TEXT, mark_tile_action_key, NORMAL_TEXT);
	printf("To move cursor left, right, up and down press '%s%c%s', '%s%c%s', '%s%c%s' and '%s%c%s' respectively.\n",
		BOLD_BRIGHT_RED_TEXT, move_cursor_left_action, NORMAL_TEXT,
		BOLD_BRIGHT_RED_TEXT, move_cursor_right_action, NORMAL_TEXT,
		BOLD_BRIGHT_RED_TEXT, move_cursor_up_action, NORMAL_TEXT,
		BOLD_BRIGHT_RED_TEXT, move_cursor_down_action, NORMAL_TEXT);
	printf("To switch debug mode press '%s%c%s'.\n", BOLD_BRIGHT_RED_TEXT, switch_debug_mode_action_key, NORMAL_TEXT);

}

std::string get_tile_char(bonus & ms, const int x, const int y)
{
	if (ms.isRevealed(x, y))
	{
		const int value = ms.valueOf(x, y);
		std::string number_plus_to_normal = string(1, '0' + value) + NORMAL_TEXT;
		switch (value)
		{
		case 0: 
			return ".";
		case 1:
			return string(BOLD_BRIGHT_BLUE_TEXT) + number_plus_to_normal;
		case 2:
			return string(BOLD_GREEN_TEXT) + number_plus_to_normal;
		case 3:
			return string(BOLD_BRIGHT_RED_TEXT) + number_plus_to_normal;
		case 4:
			return string(BOLD_BLUE_TEXT) + number_plus_to_normal;
		case 5:
			return string(BOLD_RED_TEXT) + number_plus_to_normal;
		case 6:
			return string(BOLD_CYAN_TEXT) + number_plus_to_normal;
		case 7:
			return string(BOLD_BRIGHT_WHITE_TEXT) + number_plus_to_normal;
		case 8:
			return string(BOLD_WHITE_TEXT) + number_plus_to_normal;
		default:
			throw std::logic_error("Around an opened cell there are too many mines.");
		}
	}
	else
	{
#ifdef MINESWEEPER_IS_MARKED_SUPPORTED
		if (ms.isMarked(x, y))
		{
			return (string(BOLD_BRIGHT_RED_TEXT) + "^" + NORMAL_TEXT);
		}
#endif
		return " ";

	}
}

void print_game_board(bonus & ms, const CursorPosition & cursor, const bool desired_display_minefield)
{
#ifdef MINESWEEPER_DEBUG_MODE_SUPPORTED
	const bool display_minefield = desired_display_minefield;
#else
	const bool display_minefield = false;
#endif

	std::string row;
	row.clear();

	row.resize(ms.getColNum() + 2, '-');
	row[0] = row[row.size() - 1] = '+';
	if (display_minefield)
	{
		row.resize(ms.getColNum()*2 + 3, '-');
		row[row.size() - 1] = '+';
	}
	printf("%s\n", row.c_str());
	for (int r = 0; r < ms.getRowNum(); ++r)
	{
		row.clear();
		row += '|';
		for (int c = 0; c < ms.getColNum(); ++c)
		{
			if (r == cursor.y && c == cursor.x)
			{
				row += YELLOW_BACKGROUND_TEXT;
			}
			row += get_tile_char(ms, c, r);
			if (r == cursor.y && c == cursor.x)
			{
				row += NORMAL_TEXT;
			}
		}
		row += '|';
		if (display_minefield)
		{
			for (int c = 0; c < ms.getColNum(); ++c)
			{
#ifdef MINESWEEPER_DEBUG_MODE_SUPPORTED
				const int v = ms.debugModeValueOf(c, r);
#else
				const int v = 0;
#endif
				char ch = 'x';
				if (r == cursor.y && c == cursor.x)
				{
					ch = '@';
				}
				else
				{
					if (v < 0)
					{
						ch = '*';
					}
					else if (0 == v)
					{
						ch = ' ';
					}
					else
					{
						ch = '0' + v;
					}
				}
				row += ch;
			}
			row += '|';
		}
		printf("%s\n", row.c_str());
	}
	row.clear();
	row.resize(ms.getColNum() + 2, '-');
	row[0] = row[row.size() - 1] = '+';
	if (display_minefield)
	{
		row.resize(ms.getColNum() * 2 + 3, '-');
		row[row.size() - 1] = '+';
	}
	printf("%s\n\n", row.c_str());
}

/* This should be your game UI function. If a user decides to play a game of minesweeper,
* UI interaction with a minesweeper object should be done here. For example, the repeated
* printing of the board state and handling of user game action such as left/right click
* on a particular cell should be done here
*/
void playTime(bonus& ms) {
	char action;
	bool unknown_action_input = false;
	CursorPosition cursor;
	cursor.x = cursor.y = 0;
	bool game_in_progress = false;

	bool display_minefield = false;
	ms = bonus(ms.getColNum(), ms.getRowNum(), ms.getMinesNum());
	ms.loadStatistics(statistics_file_name);

	while (1)
	{
		clear_terminal_window();
		print_game_board(ms, cursor, display_minefield);
		
		if (unknown_action_input)
		{
			print_unknown_action_error_message(action);
		}

		print_play_game_helper(game_in_progress);

		action = get_input_char();
		if (!is_game_action_key_known(action))
		{
			// we do not need to process actions that are unknown
			unknown_action_input = true;
			continue;
		}

		unknown_action_input = false;
		if (!process_game_action(action, ms, game_in_progress, display_minefield, cursor))
		{
			// Exit game loop: game is finished by user manually.
			break;
		}

		if (game_in_progress)
		{
			const int game_state = ms.endGame();
			if (0 != game_state)
			{
				game_in_progress = false;
				const char * game_end_message = "";
				// update statistics
				switch (game_state)
				{
				case -1:
					// loss
					ms.setWinStreak(0);
					ms.setLoss(ms.getLoss() + 1);
					game_end_message = "You've lost.";
					break;
				case 1:
					// win
					ms.setWins(ms.getWins() + 1);
					ms.setWinStreak(ms.getWinStreak() + 1);
					if (ms.getWinStreak() > ms.getLongestWinStreak())
					{
						ms.setLongestWinStreak(ms.getWinStreak());
					}
					game_end_message = "You win!";
					break;
				}
				ms.saveStatistics(statistics_file_name);

				if (!play_once_again(game_end_message))
				{
					// user decided not to play one more time. Exit main game loop and return back to main menu.
					break;
				}
				ms = bonus(ms.getColNum(), ms.getRowNum(), ms.getMinesNum());
				ms.loadStatistics(statistics_file_name);
			}
		}
	}
}

/* display the statistics of the game. This is a bonus point function
 */
void viewStatistics(bonus &ms) {
	clear_terminal_window();
	const char * initial_statistics_header =
		"Minesweeper statistics:\n";

	printf("%s\n\n", initial_statistics_header);
	printf("Total wins:\t%s%d%s\n", BOLD_MAGENTA_TEXT, ms.getWins(), NORMAL_TEXT);
	printf("Total losses:\t%s%d%s\n", BOLD_MAGENTA_TEXT, ms.getLoss(), NORMAL_TEXT);
	printf("Win/loss ratio:\t%s%lf%s\n", BOLD_MAGENTA_TEXT, ms.getRatio(), NORMAL_TEXT);
	printf("\n");
	printf("Current win streak:\t%s%d%s\n", BOLD_CYAN_TEXT, ms.getWinStreak(), NORMAL_TEXT);
	printf("Longest win streak:\t%s%d%s\n", BOLD_CYAN_TEXT, ms.getLongestWinStreak(), NORMAL_TEXT);
	printf("\n\n");
	printf("Press any key to return to main menu\n");
	get_input_char();
}

const char exit_action_key = 'q';
const char play_game_action_key = 'p';
const char view_stats_action_key = 's';

void print_unknown_action_error_message(const char action)
{
	printf("%sWarning!%s Unknown input action entered: '%s%c%s'\n", BOLD_YELLOW_TEXT, NORMAL_TEXT, BOLD_BRIGHT_RED_TEXT, action, NORMAL_TEXT);
}

void print_initial_actions()
{
	// iostream manipulations to get colored output is stupid. Use old-good printf instead.
	const char * initial_actions_header =
		"This is main menu for Minesweeper game.\n"
		"Possible actions are:";
	const char * action_prefix = "\t Press";
	const char * exit_game_action_msg = "to quit the game.";
	const char * play_game_action_msg = "to play a game.";
	const char * view_stats_action_msg = "to view statistics.";

	printf("%s\n", initial_actions_header);
	printf("%s '%s%c%s' %s\n", action_prefix, BOLD_BRIGHT_RED_TEXT, exit_action_key, NORMAL_TEXT, exit_game_action_msg);
	printf("%s '%s%c%s' %s\n", action_prefix, BOLD_BRIGHT_RED_TEXT, play_game_action_key, NORMAL_TEXT, play_game_action_msg);
	printf("%s '%s%c%s' %s\n", action_prefix, BOLD_BRIGHT_RED_TEXT, view_stats_action_key, NORMAL_TEXT, view_stats_action_msg);
}

bool process_action_input(const char action, bonus &ms)
{
	if (action == exit_action_key)
	{
		return false;
	}
	else if (action == view_stats_action_key)
	{
		viewStatistics(ms);
	}
	else if (action == play_game_action_key)
	{
		playTime(ms);
	}
	return true;
}

bool is_action_key_known(const char action)
{
	return action == exit_action_key || action == play_game_action_key || action == view_stats_action_key;
}

void print_good_bye_message()
{
	printf("Minesweeper game is finished. Good bye!\n");
}

} // end of anonymous namespace

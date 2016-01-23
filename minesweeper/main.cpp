#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include "minesweeper.h"
#include "bonus.h"

#include "clear_terminal_window.h"
#include "get_input_char.h"

using namespace std;

namespace
{
	void playTime(minesweeper& play);
	void viewStatistics();
	// Prints a message on the screen with warning that entered action is unknown;
	void print_unknown_action_error_message(const char action);
	// display initial actions helper on the screen.
	void print_initial_actions();
	// process user action input.
	// @return true if one more main loop iteration is required
	bool process_action_input(char action, bonus &ms);
	// Check if action key is valid and can be processed correctly.
	bool is_action_key_known(char action);
	// Display statistics on the screen and wait until user exits it.
	void display_statistics(bonus &ms);
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

/* This should be your game UI function. If a user decides to play a game of minesweeper,
* UI interaction with a minesweeper object should be done here. For example, the repeated
* printing of the board state and handling of user game action such as left/right click
* on a particular cell should be done here
*/
void playTime(minesweeper& play) {
//TODO - Begin the minesweeper game function; should interact with minesweeper class/object here
}

/* display the statistics of the game. This is a bonus point function
 */
void viewStatistics() {
    cout << "Currently Not Supported \n" << endl;
}

const char * NORMAL_TEXT = "\x1B[0m";
const char * BOLD_RED_TEXT = "\x1B[1;31m";
const char * BOLD_BRIGHT_RED_TEXT = "\x1B[38;5;09m";
const char * BOLD_GREEN_TEXT = "\x1B[1;32m";
const char * BOLD_BRIGHT_GREEN_TEXT = "\x1B[38;5;0Am";
const char * BOLD_YELLOW_TEXT = "\x1B[1;33m";
const char * BOLD_BRIGHT_YELLOW_TEXT = "\x1B[38;5;0Bm";
const char * BOLD_BLUE_TEXT = "\x1B[1;34m";
const char * BOLD_BRIGHT_BLUE_TEXT = "\x1B[38;5;0Cm";
const char * BOLD_MAGENTA_TEXT = "\x1B[1;35m";
const char * BOLD_BRIGHT_MAGENTA_TEXT = "\x1B[38;5;0Dm";
const char * BOLD_CYAN_TEXT = "\x1B[1;36m";
const char * BOLD_BRIGHT_CYAN_TEXT = "\x1B[38;5;0Em";
const char * BOLD_WHITE_TEXT = "\x1B[1;37m";
const char * BOLD_BRIGHT_WHITE_TEXT = "\x1B[38;5;0Fm";

const char exit_action_key = 'q';
const char start_game_action_key = 'n';
const char view_stats_action_key = 's';

void print_unknown_action_error_message(const char action)
{
	printf("%sWarning!%s Unknown input action entered: '%s%c%s'", BOLD_YELLOW_TEXT, NORMAL_TEXT, BOLD_BRIGHT_RED_TEXT, action, NORMAL_TEXT);
}

void print_initial_actions()
{
	// iostream manipulations to get colored output is stupid. Use old-good printf instead.
	const char * initial_actions_header =
		"This is main menu for Minesweeper game.\n"
		"Possible actions are:";
	const char * action_prefix = "\t Press";
	const char * exit_game_action_msg = "to quit the game.";
	const char * start_game_action_msg = "to start new game.";
	const char * view_stats_action_msg = "to view statistics.";

	printf("%s\n", initial_actions_header);
	printf("%s '%s%c%s' %s\n", action_prefix, BOLD_BRIGHT_RED_TEXT, exit_action_key, NORMAL_TEXT, exit_game_action_msg);
	printf("%s '%s%c%s' %s\n", action_prefix, BOLD_BRIGHT_RED_TEXT, start_game_action_key, NORMAL_TEXT, start_game_action_msg);
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
		display_statistics(ms);
	}
	else if (action == start_game_action_key)
	{
		playTime(ms);
	}
	return true;
}

bool is_action_key_known(const char action)
{
	return action == exit_action_key || action == start_game_action_key || action == view_stats_action_key;
}

void display_statistics(bonus &ms)
{
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

void print_good_bye_message()
{
	printf("Minesweeper game is finished. Good bye!\n");
}

} // end of anonymous namespace

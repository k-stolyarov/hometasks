#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include "minesweeper.h"
using namespace std;

void playTime(minesweeper& play);
void viewStatistics();

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
const char load_game_action_key = 'l';
const char view_stats_action_key = 's';

void print_initial_actions()
{
	// iostream manipulations to get colored output is stupid. Use old-good printf instead.
	const char * initial_actions_header =
		"This is main menu for Minesweeper game.\n"
		"Possible actions are:";
	const char * action_prefix = "\t Press";
	const char * exit_game_action_msg = "to exist the game.";
	const char * start_game_action_msg = "to start new game.";
	const char * load_game_action_msg = "to load saved game from file.";
	const char * view_stats_action_msg = "to view statistics.";

	printf("%s\n", initial_actions_header);
	printf("%s '%s%c%s' %s\n", action_prefix, BOLD_BRIGHT_RED_TEXT, exit_action_key, NORMAL_TEXT, exit_game_action_msg);
	printf("%s '%s%c%s' %s\n", action_prefix, BOLD_BRIGHT_RED_TEXT, start_game_action_key, NORMAL_TEXT, start_game_action_msg);
	printf("%s '%s%c%s' %s\n", action_prefix, BOLD_BRIGHT_RED_TEXT, load_game_action_key, NORMAL_TEXT, load_game_action_msg);
	printf("%s '%s%c%s' %s\n", action_prefix, BOLD_BRIGHT_RED_TEXT, view_stats_action_key, NORMAL_TEXT, view_stats_action_msg);
}

int main() {

	/* This will be your main GUI loop. You should query the user for actions such 
     * as starting a game, viewing statistics, or quitting the program. You should
     * handle user input either succinctly or by making a call to a helper method
     * to perform the desired operations.
     */
	print_initial_actions();
    while (1) {
		
        
	//TODO - Ask the user with options to perform such as Starting a game, Viewing
	// statistics, Quitting the program,  and any 
        // other functionality you feel is necessary.
        // Each iteration here is one round of the game.
	
        // somewhere you need to create a minesweeper game object first if the 
        // user decides to start a new round of game, e.g., 
        // minesweeper play();
    }
    return 0;
}

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

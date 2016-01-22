#include <cstdlib>
#include <iostream>
#include "minesweeper.h"
using namespace std;

void playTime(minesweeper& play);
void viewStatistics();

/*
 * 
 */
int main() {

    
     /* This will be your main GUI loop. You should query the user for actions such 
     * as starting a game, viewing statistics, or quitting the program. You should
     * handle user input either succinctly or by making a call to a helper method
     * to perform the desired operations.
     */
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
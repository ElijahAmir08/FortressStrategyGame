//
//  main.cpp
//  Program 3
//
//  Created by Elijah-Amir Hodges on 3/16/24.
//

#include "Game.hpp"
#include "userPlayer.hpp"
#include "computerPlayer.hpp"
#include <iostream>
#include <limits>
using namespace std;

int getIntInput(const string& prompt, int min = 1, int max = 100) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value < min || value > max) { //If there is no valid input, or beyond the range then ignore
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Cleans up the input up to a new line
            cout << "Invalid input. Please enter a number between " << min << " and " << max << ".\n";
        } else {
            break;
        }
    }
    return value;
}

void promptPlayerMove(userPlayer& player) {
    int choice;
    cout << "\nYour Turn:\n1) Regular Move\n2) Special Move\nChoice: ";
    cin >> choice;

    if (choice == 2 && player.getSpecialCount() > 0) {
        player.specialMove();
    } else {
        if (choice == 2 && player.getSpecialCount() == 0) {
            cout << "No specials left. Performing regular move.\n";
        }
        player.makeMove();
    }
}


int main(int argc, const char * argv[]) {
    cout << "===== FORT STRATEGY BATTLE GAME =====\n\n";

    int selectRow = getIntInput("Select number of rows (1-10): ", 1, 10);
    int selectCol = getIntInput("Select number of columns (1-10): ", 1, 10);
    int selectFortsPerPlayer = getIntInput("Select number of forts for each player (1-20): ", 1, 20);
    int selectSpecialPerPlayer = getIntInput("Select number of specials for each player (0-10): ", 0, 10);

    cout << "\nStarting game with a " << selectRow << "x" << selectCol << " board...\n\n";
    int maxForts = selectCol * selectRow;
    if (selectFortsPerPlayer > maxForts) {
        cout << "Too many forts for the board sie. Max allowed is " << maxForts << ".\n";
        cout << "Please try again: ";
        cin >> selectFortsPerPlayer;
    }
    Game fortGame(selectRow, selectCol, selectSpecialPerPlayer, selectFortsPerPlayer);
    extern Game* activeGame; //Tells the compiler that the game exists elsewhere
    activeGame = &fortGame;  //Point the activeGame to the current one
    fortGame.gameBegin();

    return 0;
}

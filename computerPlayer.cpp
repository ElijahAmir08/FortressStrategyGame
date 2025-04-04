//
//  computerPlayer.cpp
//  Program 3
//
//  Created by Elijah-Amir Hodges on 3/16/24.
//

#include "computerPlayer.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <utility>
using namespace std;

computerPlayer::computerPlayer(const string name, int fortCount, int specials)
: Player(name, fortCount, specials) {
    srand(static_cast<unsigned>(time(0))); // RNG seed
    
    // Initialize own and view boards
    ownBoard.resize(5, vector<string>(5, "*"));
    viewBoard.resize(5, vector<string>(5, "*"));
    // Randomly place forts on ownBoard
    int placed = 0;
    while (placed < fortCount) {
        int r = rand() % 5;
        int c = rand() % 5;
        if (ownBoard[r][c] == "*") {
            ownBoard[r][c] = "F";
            placed++;
        }
    }
}

static vector<pair<int, int>> moveHistory;
static const int MAX_ROWS = 5;
static const int MAX_COLS = 5;

bool hasMoved(int r, int c) {
    for (const auto& move : moveHistory) {
        if (move.first == r && move.second == c) {
            return true;
        }
    }
    return false;
}

void computerPlayer::makeMove() {
    int row, col;
    do {
        row = rand() % MAX_ROWS;
        col = rand() % MAX_COLS;
    } while (hasMoved(row, col)); // ensure unique move
    
    moveHistory.emplace_back(row, col); //Add move to vector moveHistory
    cout << name << " attacks position (" << row << ", " << col << ")\n";
    decrementFort();
    cout << name << " reduces enemy fort count.\n";
}

void computerPlayer::specialMove() {
    if (getSpecialCount() > 0) {
        cout << getName() << " uses a special move! Targets multiple locations.\n";
        decrementSpecial();

        for (int i = 0; i < 2; ++i) {
            makeMove();
        }
    } else {
        cout << name << " has no specials left. Defaulting to makeMove().\n";
        makeMove();
    }
}

//
//  userPlayer.cpp
//  Program 3
//
//  Created by Elijah-Amir Hodges on 3/16/24.
//

#include "userPlayer.hpp"
#include "Game.hpp"
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

Game* activeGame = nullptr; //A pointer to game so user has access the full state of the game
static vector<pair<int, int>> userMoveHistory;

int getMaxRows() {
    return activeGame->getRow();
}

int getMaxCols() {
    return activeGame->getCol();
}

userPlayer::userPlayer(const string name, int fortCount, int specials, int rows, int cols)
: Player(name, fortCount, specials) {
    ownBoard.resize(rows, vector<string>(cols, "*"));
    viewBoard.resize(rows, vector<string>(cols, "*"));

    int placed = 0;
    while (placed < fortCount) {
        int r = rand() % rows;
        int c = rand() % cols;
        if (ownBoard[r][c] == "*") {
            ownBoard[r][c] = "F";
            placed++;
        }
    }
}

bool userHasMoved(int r, int c) {
    for (const auto& move : userMoveHistory) {
        if (move.first == r && move.second == c) {
            return true;
        }
    }
    return false;
}

void userPlayer::attackCell(int row, int col, Player& cpu) {
    if (row < 0 || row >= getMaxRows() || col < 0 || col >= getMaxCols() || userHasMoved(row, col)) return;

    userMoveHistory.emplace_back(row, col);

    auto& targetBoard = cpu.getOwnBoard();

    if (targetBoard[row][col] == "F") {
        targetBoard[row][col] = "x";
        viewBoard[row][col] = "x";
        cpu.decrementFort();
        cout << "HIT! You struck a fort at (" << row << ", " << col << ")\n";
    } else {
        viewBoard[row][col] = "0";
        cout << "Missed at (" << row << ", " << col << ")\n";
    }
}
void userPlayer::makeMove() {
    int row, col;
    cout << "\nEnter row and column to attack (0-based index): ";
    cin >> row >> col;

    if (row < 0 || row >= getMaxRows() || col < 0 || col >= getMaxCols()) {
        cout << "Invalid coordinates. Try again.\n";
        return makeMove();
    }
    if (userHasMoved(row, col)) {
        cout << "You already attacked that position. Try again.\n";
        return makeMove();
    }
    userMoveHistory.emplace_back(row, col);
        decrementFort();
        cout << getName() << " attacks position (" << row << ", " << col << ")\n";
    }

Player& getCPU() {
    if (activeGame->option == 1) {
        return activeGame->Player2;
    } else {
        return activeGame->Player3;
    }
}

void userPlayer::specialMove() {
    if (getSpecialCount() <= 0) {
        cout << "No specials left. Performing regular move.\n";
        makeMove();
        return;
    }

    cout << getName() << " has " << getSpecialCount() << " special move(s) left.\n";
    cout << "Choose a special move type:\n";
    cout << "1) Double Strike (2 manual targets)\n";
    cout << "2) Diagonal Strike (from a point downward)\n";
    cout << "3) Square Strike (2x2 block)\n";
    cout << "4) Random Blitz (3 random targets)\n";
    cout << "5) Cancel\nSelection: ";

    int type;
    cin >> type;

    if (type >= 1 && type <= 4) decrementSpecial();

    switch (type) {
        case 1: { // Double Strike
            for (int i = 0; i < 2; ++i) makeMove();
            break;
        }
        case 2: { // Diagonal Strike
            int r, c;
            cout << "Enter starting point for diagonal strike: ";
            cin >> r >> c;
            for (int i = 0; i < 3; ++i) {
                attackCell(r + i, c + i, getCPU());
            }
            break;
        }
        case 3: { // Square Strike
            int r, c;
            cout << "Enter top-left of 2x2 square: ";
            cin >> r >> c;
            if (r >= 0 && r + 1 < getMaxRows() && c >= 0 && c + 1 < getMaxCols()) {
                attackCell(r, c, getCPU());
                attackCell(r, c + 1, getCPU());
                attackCell(r + 1, c, getCPU());
                attackCell(r + 1, c + 1, getCPU());
            } else {
                cout << "Invalid square placement. Try again.\n";
                return;
            }
            
        }
        case 4: { // Random Blitz
            for (int i = 0; i < 3; ++i) {
                int r = rand() % getMaxRows();
                int c = rand() % getMaxCols();
                attackCell(r, c, getCPU());
            }
            break;
        }
        default:
            cout << "Special move cancelled. Performing regular move.\n";
            makeMove();
            break;
    }
    
}

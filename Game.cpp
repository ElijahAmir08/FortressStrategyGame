//
//  Game.cpp
//  Program 3
//
//  Created by Elijah-Amir Hodges
//

#include "Game.hpp"
#include <cstdlib>
#include <ctime>

Game::Game(int row, int col, int specialsPerPlayer, int fortCount)
: row(row), col(col), userPlayer("Human", fortCount, specialsPerPlayer, row, col), Player2("Aggressive CPU", fortCount, specialsPerPlayer), Player3("Tactical CPU", fortCount, specialsPerPlayer) {
    setUpBoards();
    srand(static_cast<unsigned>(time(0))); //Seed for RNG
}

Game::~Game(){}

void Game::setUpBoards(){
    playerBoard.resize(row, vector<string>(col, "*"));
    opponentBoard.resize(row, vector<string>(col, "*"));
}


void Game::displayPlayerBoard() const{
    
    for(int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << playerBoard[i][j] << " ";
        }
        cout << endl;
    }
    
}

void Game::displayOpponentBoard() const{
    
    for(int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << opponentBoard[i][j] << " ";
        }
        cout << endl;
    }
    
}

void Game::updatePlayerBoard(int r, int c) {
    if(r >= 0 && r < row && c >= 0 && c < col) {
        playerBoard[r][c] = "0";
    }
}

void Game::updateOpponentBoard(int r, int c) {
    if(r >= 0 && r < row && c >= 0 && c < col) {
        opponentBoard[r][c] = "0";
    }
}


void Game::gameBegin() {
    cout << "Select opponent type:\n1.) Aggressive opponent\n2.) Tactical opponent\n";
    cin >> option;

    while (true) {
        // Check win/lose before turn
        if (userPlayer.getFortCount() <= 0) {
            cout << "\nYou LOSE.\n";
            break;
        }
        if (option == 1 && Player2.getFortCount() <= 0) {
            cout << "\nYou WIN!\n";
            break;
        }
        if (option == 2 && Player3.getFortCount() <= 0) {
            cout << "\nYou WIN!\n";
            break;
        }

        // === PLAYER TURN ===
        cout << "\n=== YOUR TURN ===\n";
        userPlayer.displayStatus();

        cout << "Your Board:\n";
        for (const auto& row : userPlayer.getOwnBoard()) {
            for (const auto& cell : row) {
                if (cell == "F") {
                    cout << "* ";
                } else {
                    cout << cell << " ";
                }
            }
            cout << endl;
        }

        cout << "Opponent Board View:\n";
        for (const auto& row : userPlayer.getViewBoard()) {
            for (const auto& cell : row) cout << cell << " ";
            cout << endl;
        }

        int moveType;
        cout << "\nChoose move: 1) Regular 2) Special\n";
        cin >> moveType;

        if (moveType == 2 && userPlayer.getSpecialCount() > 0) {
            userPlayer.specialMove();
        } else {
            userPlayer.makeMove();
        }

        // Check if CPU lost after player move
        if (option == 1 && Player2.getFortCount() <= 0) {
            cout << "\nYou WIN!\n";
            break;
        }
        if (option == 2 && Player3.getFortCount() <= 0) {
            cout << "\nYou WIN!\n";
            break;
        }

        // === CPU TURN ===
        cout << "\n=== CPU TURN ===\n";
        if (option == 1) {
            Player2.displayStatus();
            Player2.makeMove();
        } else {
            Player3.displayStatus();
            Player3.makeMove();
        }

        // Check if player lost after CPU move
        if (userPlayer.getFortCount() <= 0) {
            cout << "\nYou LOSE.\n";
            break;
        }
    }
}




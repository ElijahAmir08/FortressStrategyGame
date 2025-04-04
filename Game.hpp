//
//  Game.hpp
//  Program 3
//
//  Created by Elijah-Amir Hodges
//

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "userPlayer.hpp"
#include "computerPlayer.hpp"
using namespace std;

class Game {
public:
    Game(int row, int col, int specialsPerPlayer, int fortCount);
    ~Game();
    
    void gameBegin();
    void setUpBoards();
    void displayPlayerBoard() const;
    void displayOpponentBoard() const;
    void updatePlayerBoard(int r, int c);
    void updateOpponentBoard(int r, int c);
    int getRow() const { return row; }
    int getCol() const { return col; }
    Player& getCurrentCPU();
    userPlayer userPlayer;
    computerPlayer Player2;
    computerPlayer Player3;
    int row, col, option;
private:
    int fortCount;
    int specialPerPlayer;
    vector<vector<string>> playerBoard;
    vector<vector<string>> opponentBoard;
    
    
};

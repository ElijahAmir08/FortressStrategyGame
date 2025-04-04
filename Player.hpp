//
//  Player.hpp
//  Program 3
//
//  Created by Elijah-Amir Hodges on 3/16/24.
//

#ifndef Player_hpp
#define Player_hpp
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
using namespace std;

class Player {
protected:
    string name;
    int fortCount;
    int specials;
    vector<vector<string>> ownBoard;     // The player's board
    vector<vector<string>> viewBoard;    // The view of opponent's board

public:
    Player(const string name, int fortCount, int specials);
    virtual ~Player();

    void displayStatus();
    const string& getName() const;
    int getFortCount() const;
    int getSpecialCount() const;
    void decrementFort();
    void decrementSpecial();
    
    vector<vector<string>>& getOwnBoard();
    vector<vector<string>>& getViewBoard();
};
#endif /* Player_hpp */

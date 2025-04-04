//
//  userPlayer.hpp
//  Program 3
//
//  Created by Elijah-Amir Hodges on 3/16/24.
//

#ifndef userPlayer_hpp
#define userPlayer_hpp
#include "Player.hpp"
#include <stdio.h>

class userPlayer : public Player {
public:
    userPlayer(const string name, int fortCount, int specials, int rows, int cols);
    void makeMove();
    void specialMove();
private:
    void attackCell(int row, int col, Player& cpu);
    
};


#endif /* userPlayer_hpp */

//
//  computerPlayer.hpp
//  Program 3
//
//  Created by Elijah-Amir Hodges on 3/16/24.
//

#ifndef computerPlayer_hpp
#define computerPlayer_hpp
#include "Player.hpp"
#include <stdio.h>

class computerPlayer : public Player {
public:
    computerPlayer(const string name, int fortCount, int specials);
    void makeMove();
    void specialMove();
    
};

#endif /* computerPlayer_hpp */

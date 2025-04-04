//
//  Player.cpp
//  Program 3
//
//  Created by Elijah-Amir Hodges
//

#include "Player.hpp"
#include <iostream>
using namespace std;

Player::Player(const string name, int fortCount, int specials)
: name(name), fortCount(fortCount), specials(specials){}

Player::~Player() {}
void Player::displayStatus() {
    cout << "Player: " << name << endl;
    cout << "Forts: " << fortCount << " | Specials: " << specials << endl;
}

const string& Player::getName() const {
    return name;
}

int Player::getFortCount() const {
    return fortCount;
}

int Player::getSpecialCount() const {
    return specials;
}

void Player::decrementFort() {
    if (fortCount > 0) fortCount--;
}

void Player::decrementSpecial() {
    if (specials > 0) specials--;
}
vector<vector<string>>& Player::getOwnBoard() {
    return ownBoard;
}

vector<vector<string>>& Player::getViewBoard() {
    return viewBoard;
}


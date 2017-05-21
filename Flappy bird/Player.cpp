//
//  Player.cpp
//  Flapi Pig
//
//  Created by Ruben on 13/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#include "Player.hpp"
Player::Player() : GameObject(){}
Player::Player(Box body, int firstScore) : GameObject(body)
{
    score = firstScore;
}

Player::~Player(){};

void Player::update(float dt)
{
    //printf("Player updated");
}

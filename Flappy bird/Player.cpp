//
//  Player.cpp
//  Flapi Pig
//
//  Created by Ruben on 13/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#include "Player.hpp"

Player::Player(int firstScore)
{
    score = firstScore;
    setGeometry();
    setColor();
}

Player::~Player(){};

void Player::update(float dt)
{
    //printf("Player updated");
}


void Player::setGeometry() {
    kmGLVec4 red = kmGLVec4Make(1.0, 0.0, 0.0, 1.0);
    kmGLVec4 blue = kmGLVec4Make(0.0, 0.0, 1.0, 1.0);
    kmGLVec4 green = kmGLVec4Make(0.0, 1.0, 0.0, 1.0);


    GLVertex gv1(kmGLVec3Make(0.0, 0.0, 0.0), red);
    GLVertex gv2(kmGLVec3Make(0.5, 0.0, 0.0),blue);
    GLVertex gv3(kmGLVec3Make(0.0, 0.5, 0.0), green);
    GLVertex gv4(kmGLVec3Make(0.5, 0.5, 0.0),red);
    
    vertexs.push_back(gv1.glVertex());
    vertexs.push_back(gv2.glVertex());
    vertexs.push_back(gv3.glVertex());
    vertexs.push_back(gv4.glVertex());
    
    
    indexs.push_back(0);
    indexs.push_back(1);
    indexs.push_back(2);
    indexs.push_back(3);
}

void Player::setColor() {

}

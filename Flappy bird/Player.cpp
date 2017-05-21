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
    //setGeometry(0);
    setColor();
}

Player::Player(Box body, int firstScore, int i) : GameObject(body)
{
    score = firstScore;
    setGeometry(i);
    setColor();
}

Player::~Player(){};

void Player::update(float dt)
{
    //printf("Player updated");
}


void Player::setGeometry(int i) {
    kmVec4 red = kmVec4Make(1.0, 0.0, 0.0, 1.0);
    kmVec4 blue = kmVec4Make(0.0, 0.0, 1.0, 1.0);
    kmVec4 green = kmVec4Make(0.0, 1.0, 0.0, 1.0);
    
    vector<kmVec3> boxV = body.getVertexs();
    if(i == 0) {
        GLVertex gv1(boxV[0], red);
        GLVertex gv2(boxV[1],blue);
        GLVertex gv3(boxV[2], green);
        GLVertex gv4(boxV[3],red);
        
        vertexs.push_back(gv1.glVertex());
        vertexs.push_back(gv2.glVertex());
        vertexs.push_back(gv3.glVertex());
        vertexs.push_back(gv4.glVertex());
        
        
        indexs.push_back(0);
        indexs.push_back(1);
        indexs.push_back(2);
        indexs.push_back(3);

    }
    else {
        GLVertex gv1(kmVec3Make(-0.5, -0.5, 0.0), red);
        GLVertex gv2(kmVec3Make(0.0, -0.5, 0.0), blue);
        GLVertex gv3(kmVec3Make(-0.5, 0.0, 0.0), green);
        GLVertex gv4(kmVec3Make(0.0, 0.0, 0.0), red);
        
        
        //degenerate triangle
        GLVertex gv5(kmVec3Make(0.5, 0.5, 0.0),red);
        vertexs.push_back(gv5.glVertex());
        vertexs.push_back(gv5.glVertex());
        vertexs.push_back(gv1.glVertex());
        vertexs.push_back(gv1.glVertex());
        indexs.push_back(4);
        indexs.push_back(5);
        indexs.push_back(6);
        indexs.push_back(7);
        
        
        //2nd triangle
        vertexs.push_back(gv1.glVertex());
        vertexs.push_back(gv2.glVertex());
        vertexs.push_back(gv3.glVertex());
        vertexs.push_back(gv4.glVertex());
        indexs.push_back(8);
        indexs.push_back(9);
        indexs.push_back(10);
        indexs.push_back(11);

    }
  }

void Player::setColor() {

}

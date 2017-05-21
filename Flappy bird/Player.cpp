//
//  Player.cpp
//  Flapi Pig
//
//  Created by Ruben on 13/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#include "Player.hpp"

Player::Player(kmVec3 position, int firstScore, int i) : GameObject(position)
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
    kmGLVec4 red = kmGLVec4Make(1.0, 0.0, 0.0, 1.0);
    kmGLVec4 blue = kmGLVec4Make(0.0, 0.0, 1.0, 1.0);
    kmGLVec4 green = kmGLVec4Make(0.0, 1.0, 0.0, 1.0);
    
    if(i == 0) {
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
    else {
        kmGLVec4 red = kmGLVec4Make(1.0, 0.0, 0.0, 1.0);
        kmGLVec4 blue = kmGLVec4Make(0.0, 0.0, 1.0, 1.0);
        kmGLVec4 green = kmGLVec4Make(0.0, 1.0, 0.0, 1.0);

        GLVertex gv1(kmGLVec3Make(-0.5, -0.5, 0.0), red);
        GLVertex gv2(kmGLVec3Make(-0.1, -0.5, 0.0), blue);
        GLVertex gv3(kmGLVec3Make(-0.5, 0.0, 0.0), green);
        GLVertex gv4(kmGLVec3Make(-0.1, 0.0, 0.0), red);
        
        
        //degenerate triangle
        GLVertex gv5(kmGLVec3Make(0.5, 0.5, 0.0),red);
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

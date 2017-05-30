//
//  Player.cpp
//  Flapi Pig
//
//  Created by Ruben on 13/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#define K_PLAYER_JUMP 10000
#include "Player.hpp"
Player::Player() : GameObject(){}
Player::Player(GBox body, int firstScore) : GameObject(body)
{
    kmSize size = body.getSize();
    score = firstScore;
    
    GLfloat w = (size.w*ASPECT_RATIO)/SCREEN_WIDTH;
    GLfloat h = size.h/SCREEN_HEIGHT;

    GLfloat h2 = h/2.0;
    GLfloat w2 = w/2.0;
    
    
    glVertex modelVertexs[] = {
        {{-w2, h2, 0},{1,0,0,1}},
        {{w2, h2, 0},{0,1,0,1}},
        {{-w2, -h2, 0},{0,0,1,1}},
        {{w2,-h2, 0},{1,0,0,1}}
    };
    
    resetModelView();
    //moveTo(kmVec3Make(100, 100, 0.0));
    GLubyte modelIndexs[] = {0,1,2,3};
    modelMesh = new GVertexArray(modelVertexs, modelIndexs);
}

Player::~Player(){};

void Player::jump() {
    body.setVelocity(kmVec3Make(0, 0, 0));
    body.applyImpulse(K_PLAYER_JUMP, kmVec3Make(0, -1, 0));
}
void Player::update(float dt)
{
    kmVec3 nextPosition = body.update(dt);
    moveTo(nextPosition);
}

void Player::render() {
    
    GLMatrix projection;
    projection.populateOrtho(0, ASPECT_RATIO, 1, 0, -1, 1);
    
    GShader::BIRD->enable();
    GShader::BIRD->enableVertexAttribute("Position");
    GShader::BIRD->enableVertexAttribute("SourceColor");
    
    kmMat4 gMatrix;
    modelView.gMatrix(&gMatrix);
    GShader::BIRD->setUniform4f("ModelView", gMatrix.mat);
    GShader::BIRD->setUniform4f("Projection", projection.matrix());
    
    kmVec3 position = getBox()->getCenter();
    GShader::BIRD->setUniform1f("xPosition", position.x);
    GShader::BIRD->setUniform1f("yPosition", SCREEN_HEIGHT - position.y);
    GShader::BIRD->setUniform1f("radius", 15.0);
    
    modelMesh->render();
    resetModelView();
    GShader::BIRD->disable();
    

};

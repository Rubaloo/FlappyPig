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
    modelView.populateIdentity();
    moveTo(body.getCenter());
    GLubyte modelIndexs[] = {0,1,2,3};
    modelMesh = new VertexArray(modelVertexs, modelIndexs);
}

Player::~Player(){};

void Player::jump() {
    body.setVelocity(kmVec3Make(0, 0, 0));
    body.applyImpulse(35, kmVec3Make(0, -1, 0));
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
    GShader::BIRD->setUniform1f("ScreenWidth", SCREEN_WIDTH);
    GShader::BIRD->setUniform1f("ScreenHeight", SCREEN_HEIGHT);
    GShader::BIRD->setUniform1f("radius", 15.0);
    modelMesh->render();
    resetModelView();
    GShader::BIRD->disable();
    

};

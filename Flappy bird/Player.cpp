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
    
    GLfloat h2 = size.h/2.0;
    GLfloat w2 = size.w/2.0;
    
    glVertex modelVertexs[] = {
        {{-w2, h2,0},{1,0,0,1}},
        {{w2, h2,0},{0,1,0,1}},
        {{-w2, -h2, 0},{0,0,1,1}},
        {{w2,-h2,0},{1,0,0,1}}
    };
    
    modelView.populateFromTranslation(body.getCenter());
    GLubyte modelIndexs[] = {0,1,2,3};
    modelMesh = new VertexArray(modelVertexs, modelIndexs);
}

Player::~Player(){};

int i = 0;
void Player::update(float dt)
{
    kmVec3 nextPosition = body.update(dt);
    modelView.populateFromTranslation(nextPosition);
}

void Player::render() {
    
    GLMatrix projection;
    projection.populateOrtho(0, ASPECT_RATIO, 1, 0, -1, 1);
    
    GShader::BIRD->enable();
    GShader::BIRD->enableVertexAttribute("Position");
    GShader::BIRD->enableVertexAttribute("SourceColor");
    GShader::BIRD->setUniform4f("ModelView", modelView.matrix());
    GShader::BIRD->setUniform4f("Projection", projection.matrix());
    modelMesh->render();
    GShader::BIRD->disable();
    

};

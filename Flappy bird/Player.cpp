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
    modelView.populateFromTranslation(kmVec3Make(0, 0, 0));
    
    glVertex modelVertexs[] = {
        {{-1,-1,0},{1,0,0,1}},
        {{1,-1,0},{0,1,0,1}},
        {{-1, 1, 0},{0,0,1,1}},
        {{1, 1,0},{1,0,0,1}}
    };
    
    GLubyte modelIndexs[] = {0,1,2,3};
    modelMesh = new VertexArray(modelVertexs, modelIndexs);
}

Player::~Player(){};

kmVec3 gravity = kmVec3Make(0.0, -9.81, 0.0);
kmVec3 impulse = kmVec3Make(0.0, 100.0, 0.0);
kmVec3 totalForce = gravity;
int i = 0;
void Player::update(float dt)
{
    
    if(i == 0) impulse = kmVec3Make(0.0, 100.0, 0.0);
    else impulse = kmVec3Make(impulse.x, (impulse.y > dt) ? impulse.y - dt*100 : 0, impulse.z);
    ++i;
    float mass = 1;
    
    totalForce = kmVec3Make(impulse.x + gravity.x, impulse.y + gravity.y, impulse.z + gravity.z);
    
    kmVec3 acceleration = kmVec3Make(totalForce.x/mass, totalForce.y/mass, totalForce.z/mass);
    kmVec3 velocity = kmVec3Make(acceleration.x * dt, acceleration.y * dt, acceleration.z * dt);
    kmVec3 position = kmVec3Make(velocity.x * dt, velocity.y * dt, velocity.z * dt);
    
    //printf("Total Force: %fx %fy %fz \n", totalForce.x, totalForce.y, totalForce.z);
    printf("next position: %f x %f y %fz \n", position.x, position.y, position.z);
}

void Player::render() {
    
    GLMatrix projection;
    projection.populateOrtho(-1, 1, -1, 1, -1, 1);
    
    printf("Player render");
    GShader::BIRD->enable();
    GShader::BIRD->enableVertexAttribute("Position");
    GShader::BIRD->enableVertexAttribute("SourceColor");
    GShader::BIRD->setUniform4f("ModelView", modelView.matrix());
    GShader::BIRD->setUniform4f("Projection", projection.matrix());
    modelMesh->render();
    GShader::BIRD->disable();
    

};

//
//  GameWorld.cpp
//  Flapi Pig
//
//  Created by Ruben on 13/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#include "GameWorld.hpp"
#include "Pipe.hpp"
#include <stdlib.h>

#define K_PIPES_COLUMNS_NUMBER 100
#define K_PIPES_OFFSET 250
#define SCREEN_TOUCH 0

GameWorld::GameWorld()
{
    end = false;
    lastPipeColumnX = -1;
    
    GShader::loadAll();
    mm = new GInputManager();
}

void GameWorld::initLevel()
{
    //Add Bird
    GBox pBox(SCREEN_CENTER, kmSizeMake(30, 30), CIRCULAR_SHAPE);
    pBox.enableGravity();
    bird = new Bird(pBox, 0);
    
    //Add pipes
    float columnPipes = K_PIPES_COLUMNS_NUMBER;
    for(int i = 0; i < columnPipes; ++i) {
        GLfloat pipeX = SCREEN_WIDTH * 1.5 + (K_PIPES_OFFSET*i);
        PipeColumn* pc = new PipeColumn(pipeX);
        cPipes.push_back(pc);
    }
}

void GameWorld::resetLevel()
{
    delete bird;
    for (int i = 0; i < cPipes.size(); ++i) {
        delete cPipes[i];
    }
    cPipes.clear();
    queue<int> empty;
    swap(messages, empty);
    initLevel();
}

GameWorld::~GameWorld()
{
}

void GameWorld::render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 104.0/255.0, 55.0/255.0, 1.0);
    
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    
    bird->render();
    for(int i = 0; i < cPipes.size(); ++i) {
        cPipes[i]->render();
    }
}

void GameWorld::logic()
{
    updateCPipes();
    processMessages();
    checkEndConditions();
}

void GameWorld::updateCPipes()
{
    for(int i = 0; i < cPipes.size(); ++i) {
        PipeColumn* pc = cPipes[i];
        if(pc->outsideLeftLimits()) {
            if(lastPipeColumnX == -1) {
                lastPipeColumnX = cPipes[cPipes.size()-1]->getUpPipe()->getBox()->getCenter().x;
            }
            float offset = 0;
            offset = lastPipeColumnX + K_PIPES_OFFSET;
            
            Pipe*up = pc->getUpPipe();
            kmVec3 next = up->getBox()->getCenter();
            
            pc->moveTo(next.x + offset);
            lastPipeColumnX = next.x + offset;
        }
    }
}

void GameWorld::processMessages()
{
    for(int i = 0; i < messages.size(); ++i) {
        int messageId = messages.front();
        messages.pop();
        switch (messageId) {
            case SCREEN_TOUCH:
                bird->jump();
                break;
            default:
                break;
        }
    }

}

void GameWorld::checkEndConditions()
{
    end = (bird->reachFloor() || bird->reachTop());
    if(!end) {
        for(int i = 0; i < cPipes.size(); ++i) {
            PipeColumn* pc = cPipes[i];
            if(pc->intersect(bird)){
                end = true;
            }
        }
    }
}

void GameWorld::update(float dt)
{
    bird->update(dt);
    for(int i = 0; i < cPipes.size(); ++i) {
        cPipes[i]->update(dt);
    }
}

void GameWorld::pollUpdates() {
    int msgNumber = mm->getInputsNumber();
    if(msgNumber > 0) {
        for(int i = 0; i < msgNumber; ++i) {
            messages.push(mm->remove());
        }
    }
}

void GameWorld::handleMessage(int msg)
{
    mm->addInput(msg);
}

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

GameWorld::GameWorld(float gGravity)
{
    GShader::loadAll();
    gravity = gGravity;
    mm = new MessageManager();
}

void GameWorld::initLevel()
{
    //Add pipes
    float columnPipes = K_PIPES_COLUMNS_NUMBER;
    
    for(int i = 0; i < columnPipes; ++i) {
        GLfloat pipeX = SCREEN_WIDTH * 1.5 + (K_PIPES_OFFSET*i);
        PipeColumn* pc = new PipeColumn(pipeX);
        cPipes.push_back(pc);
    }
    
    //Add player
    // Trabajar en cordenadas de pantalla y establecer escena inicial antes de empezar con las fisicas
    Box pBox(kmVec3Make(SCREEN_WIDTH/2.0, SCREEN_HEIGHT/2.0, 0.0), kmSizeMake(30, 30));
    pBox.enableGravity();
    bird = new Player(pBox, 0);
}

GameWorld::~GameWorld()
{
    GShader::loadAll();
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

bool GameWorld::add(GameObject *gObject)
{
    //gObjects.push_back(gObject);
    return true;
}

void GameWorld::logic()
{
    //bird->resetModelView();
    for(int i = 0; i < cPipes.size(); ++i) {
        PipeColumn* pc = cPipes[i];
        if(pc->outsideLeftLimits()) {
            if(!lastPc) lastPc = cPipes[cPipes.size()-1];
            float offset = 0;
            offset = lastPc->getUpPipe()->getBox()->getCenter().x + K_PIPES_OFFSET;
            
            Pipe*up = pc->getUpPipe();
            kmVec3 next = up->getBox()->getCenter();
            pc->moveTo(next.x + offset);
            lastPc = (PipeColumn*)cPipes[i];
            printf("outside left limits %i\n", i); //addPipes
        }
    }

    
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
    
    for(int i = 0; i < cPipes.size(); ++i) {
        PipeColumn* pc = cPipes[i];
        if(pc->intersect(bird)){
            running = false;
            //printf("HAS CHOCADO NOOOOOOOOB\n");
            //sendMessage(running);
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
    int msgNumber = mm->getMessagesNumber();
    if(msgNumber > 0) {
        for(int i = 0; i < msgNumber; ++i) {
            messages.push(mm->remove());
        }
    }
}

void GameWorld::handleMessage(int msg)
{
    mm->add(msg);
}

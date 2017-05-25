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

#define SCREEN_TOUCH 0

GameWorld::GameWorld(float gGravity)
{
    GShader::loadAll();
    gravity = gGravity;
    mm = new MessageManager();
}

void GameWorld::initLevel()
{
    //Add player
    // Trabajar en cordenadas de pantalla y establecer escena inicial antes de empezar con las fisicas
    kmSize screen = GDirector::getInstance()->getWinSizeInPixels();
    float x = screen.w/2.0;
    float y = screen.h/2.0;
    Box pBox(kmVec3Make(15, 15, 0.0), kmSizeMake(30, 30));
    pBox.enableGravity();
    bird = new Player(pBox, 0);
    gObjects.push_back(bird);
    

    //Add pipes
    
    float numPipes = 1;
    float offset = 60;
    float space = 100;
    float pipeHeight = 100;
    float pipeWidth = 50;
    
    for(int i = 0; i < numPipes; ++i) {
        GLfloat pipeX = SCREEN_WIDTH/2.0 + (offset*i);
        
        Box uPipeBox(kmVec3Make(pipeX, 0.0, 0.0), kmSizeMake(pipeWidth, pipeHeight));
        Box dPipeBox(kmVec3Make(pipeX, pipeHeight+space , 0.0), kmSizeMake(pipeWidth, SCREEN_HEIGHT-pipeHeight+space));
        
        Pipe* up = new Pipe(uPipeBox);
        //Pipe* dp = new Pipe(dPipeBox);
        
        gObjects.push_back(up);
        //gObjects.push_back(dp);
        
    }
}

GameWorld::~GameWorld()
{
    GShader::loadAll();
}

void GameWorld::render()
{
    kmSize screenSize = GDirector::getInstance()->getWinSizeInPixels();
    glClearColor(0, 104.0/255.0, 55.0/255.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glViewport(0, 0, screenSize.w, screenSize.h);
    //painter->render(gObjects);
    
    for(int i = 0; i < gObjects.size(); ++i) {
        gObjects[i]->render();
    }
}

bool GameWorld::add(GameObject *gObject)
{
    gObjects.push_back(gObject);
    return true;
}

void GameWorld::logic()
{
    for(int i = 0; i < messages.size(); ++i) {
        int messageId = messages.front();
        messages.pop();
        switch (messageId) {
            case SCREEN_TOUCH:
                bird->getBox()->applyImpulse(100,kmVec3Make(0, -1, 0));
                break;
                
            default:
                break;
        }
        
    }

}

void GameWorld::update(float dt)
{
    for(int i = 0; i < gObjects.size(); ++i) {
        gObjects[i]->update(dt);
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

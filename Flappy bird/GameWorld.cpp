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
    

    //Add pipes
    
    float columnPipes = 10;
    float offset = 250;
    float space = 150;
    float pipeVelocity = -100;
    float pipeWidth = 50;
    
    
    for(int i = 0; i < columnPipes; ++i) {
        GLfloat pipeX = SCREEN_WIDTH * 1.5 + (offset*i);
        //addColumnPipe(previousPipe, );
        
        
    
        float uPipeHeight = rand() % 200 + 100;
        float dPipeHeight = SCREEN_HEIGHT - uPipeHeight - space;
        
        Box uPipeBox(kmVec3Make(pipeX, uPipeHeight/2.0, 0.0), kmSizeMake(pipeWidth, uPipeHeight));
       Box dPipeBox(kmVec3Make(pipeX, SCREEN_HEIGHT - (dPipeHeight/2.0), 0.0), kmSizeMake(pipeWidth, dPipeHeight));
        uPipeBox.setVelocity(kmVec3Make(pipeVelocity, 0, 0));
        dPipeBox.setVelocity(kmVec3Make(pipeVelocity, 0, 0));
        
        Pipe* up = new Pipe(uPipeBox);
        Pipe* dp = new Pipe(dPipeBox);
        
        gObjects.push_back(up);
        gObjects.push_back(dp);
        
        pipes.push_back(up);
        pipes.push_back(dp);
    }
    
    //Add player
    // Trabajar en cordenadas de pantalla y establecer escena inicial antes de empezar con las fisicas
    Box pBox(kmVec3Make(SCREEN_WIDTH/2.0, SCREEN_HEIGHT/2.0, 0.0), kmSizeMake(30, 30));
    pBox.enableGravity();
    bird = new Player(pBox, 0);
    gObjects.push_back(bird);

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
    for(int i = 0; i < pipes.size(); i+=2) {
        Pipe* up = pipes[i];
        Pipe* dp = pipes[i+1];
        
        if(up->outsideLeftLimits()) {
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
    
    
    for(int i = 0; i < pipes.size(); ++i) {
        Box* pipeBox = pipes[i]->getBox();
        
        if(bird->getBox()->intersect(pipeBox)){
            running = false;
            printf("HAS CHOCADO NOOOOOOOOB\n");
            //sendMessage(running);
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

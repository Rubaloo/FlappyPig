//
//  GameWorld.cpp
//  Flapi Pig
//
//  Created by Ruben on 13/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#include "GameWorld.hpp"
#include "Player.hpp"
#include <stdlib.h>

GameWorld::GameWorld(float gGravity)
{
    GShader::loadAll();
    gravity = gGravity;
    painter = new Renderer();
    painter->setupRenderContext();
}

void GameWorld::initLevel()
{
    //Add player
    // Trabajar en cordenadas de pantalla y establecer escena inicial antes de empezar con las fisicas
    Box pBox(kmVec3Make(0.0, 0.0, 0.0), kmSizeMake(0.50, 0.50));
    Player *p = new Player(pBox, 0);
    gObjects.push_back(p);

    
    //Add pipes
//    int numPipes = 3;
//    for(int i = 0; i < numPipes; ++i) {
//        Pipe* p = new Pipe(6);
//        gObjects.push_back(p);
//    }
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

void GameWorld::update(float dt)
{
    for(int i = 0; i < gObjects.size(); ++i) {
        gObjects[i]->update(dt);
    }
}

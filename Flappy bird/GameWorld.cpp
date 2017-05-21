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
    gravity = gGravity;
    painter = new Renderer();
    painter->setupRenderContext();
}

void GameWorld::initLevel()
{
    //Add player
    Box pBox(kmVec3Make(0.25, 0.25, 0.0),kmSizeMake(0.5, 0.5));
    Player *p = new Player(pBox, 0);
    gObjects.push_back(p);
//    Box p2Box(kmVec3Make(-0.25, -0.25, 0.0),kmSizeMake(0.5, 0.5));
//    Player *p2 = new Player(p2Box, 0, 1);
//    gObjects.push_back(p2);

    
    //Add pipes
//    int numPipes = 3;
//    for(int i = 0; i < numPipes; ++i) {
//        Pipe* p = new Pipe(6);
//        gObjects.push_back(p);
//    }
}

GameWorld::~GameWorld()
{
    
}

void GameWorld::render()
{
    painter->render(gObjects);
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

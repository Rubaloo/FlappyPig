//
//  PipeColumn.cpp
//  Flappy bird
//
//  Created by Ruben on 27/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//


#include "PipeColumn.hpp"


PipeColumn::PipeColumn(){}
PipeColumn::PipeColumn(int xCenter) {
    float uPipeHeight = rand() % 200 + 100;
    float dPipeHeight = SCREEN_HEIGHT - uPipeHeight - K_COLUMN_PIPES_SPACE;
    
    Box uPipeBox(kmVec3Make(xCenter, uPipeHeight/2.0, 0.0), kmSizeMake(K_COLUMN_PIPES_WIDTH, uPipeHeight));
    Box dPipeBox(kmVec3Make(xCenter, SCREEN_HEIGHT - (dPipeHeight/2.0), 0.0), kmSizeMake(K_COLUMN_PIPES_WIDTH, dPipeHeight));
    uPipeBox.setVelocity(kmVec3Make(k_COLUMN_SPEED, 0, 0));
    dPipeBox.setVelocity(kmVec3Make(k_COLUMN_SPEED, 0, 0));
    
    up = new Pipe(uPipeBox);
    down = new Pipe(dPipeBox);
}

bool PipeColumn::intersect(GameObject* gObject)
{
    return (up->intersect(gObject)) || (down->intersect(gObject));
}

void PipeColumn::update(float dt)
{
    up->update(dt);
    down->update(dt);
}

bool PipeColumn::outsideLeftLimits()
{
    return up->outsideLeftLimits() || down->outsideLeftLimits();
}

void PipeColumn::render() {
    up->render();
    down->render();
};

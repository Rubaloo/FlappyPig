//
//  Box.cpp
//  Flappy bird
//
//  Created by Ruben on 21/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#include "Box.hpp"
#define K_GRAVITY -1.0

Box::Box(){};
Box::Box(kmVec3 c, kmSize s)
{
    center = c;
    size = s;
    
    velocity = kmVec3Make(0, 0, 0);
    mass = 1;
    
    isVisible = true;
    gravityEnabled = false;
    endForce = kmVec3Make(0, 0, 0);
}

void Box::updateEndForce()
{
    for(int i = 0; i < forces.size(); ++i) {
        endForce = kmVec3Add(endForce, forces[i]);
    }
}


void Box::enableGravity()
{
    kmVec3 gravityForce = kmVec3Make(0.0, K_GRAVITY, 0.0);
    forces.push_back(gravityForce);
    updateEndForce();
}

//triangle strip box representation
vector<kmVec3> Box::getVertexs()
{
    vector<kmVec3> vertexs;
    GLfloat hWidth = size.w/2.0;
    GLfloat hHeight = size.h/2.0;
    
    kmVec3 bl = kmVec3Make(center.x - hWidth , center.y - hHeight, 0.0);
    kmVec3 br = kmVec3Make(center.x + hWidth , center.y - hHeight, 0.0);
    kmVec3 tl = kmVec3Make(center.x - hWidth , center.y + hHeight, 0.0);
    kmVec3 tr = kmVec3Make(center.x + hWidth , center.y + hHeight, 0.0);
    
    vertexs.push_back(bl); vertexs.push_back(br); vertexs.push_back(tl); vertexs.push_back(tr);
    return vertexs;
}



kmVec3 Box::getCenter()
{
    return center;
}

void Box::applyImpulse(float force, kmVec3 direction)
{
    kmVec3 forceI = kmVec3Make(force * direction.x, force * direction.y, force * direction.z);
    endForce = kmVec3Make(endForce.x + forceI.x, endForce.y + forceI.y, endForce.z + forceI.z);
}

kmVec3 Box::update(float dt)
{
    kmVec3 nextPosition = kmVec3Make(0, 0, 0);
    
    kmVec3 acceleration = kmVec3Make(endForce.x/mass, endForce.y/mass, endForce.z/mass);
    kmVec3 v = kmVec3Make(acceleration.x * dt, acceleration.y * dt, acceleration.z * dt);
    
    velocity = kmVec3Make(v.x + velocity.x, v.y + velocity.y, v.z + velocity.z);
    
    kmVec3 step = kmVec3Make(velocity.x * dt, velocity.y * dt, velocity.z * dt);
    nextPosition = kmVec3Make(center.x + step.x, center.y + step.y, center.z + step.z);
    setCenter(nextPosition);
    //printf("next position: %f x %f y %fz \n", step.x, step.y, step.z);
    
    return nextPosition;
}

void Box::setCenter(kmVec3 c)
{
    center = c;
}


bool Box::moveTo(kmVec3 direction) {
    return true;
};

bool Box::intersect(Box* gameObject) {
    return true;
};

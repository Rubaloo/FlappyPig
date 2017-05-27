//
//  Box.cpp
//  Flappy bird
//
//  Created by Ruben on 21/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#include "Box.hpp"
#include "GDirector.hpp"
#include <cmath>
#define K_GRAVITY 50.0

Box::Box(){};
Box::Box(kmVec3 position, kmSize s)
{
    center = kmVec3Make(position.x, position.y, 0);
    
    // Size change
    size = kmSizeMake(s.w, s.h);
    
    velocity = kmVec3Make(0, 0, 0);
    mass = 1;
    
    isVisible = true;
    gravityEnabled = false;
    endForce = kmVec3Make(0, 0, 0);
}

void Box::updateEndForce()
{
    endForce = kmVec3Make(0,0,0);
    for(int i = 0; i < constantForces.size(); ++i) {
        endForce = kmVec3Add(endForce, constantForces[i]);
    }
    
    for(int i = 0; i < momentForces.size(); ++i) {
        endForce = kmVec3Add(endForce, momentForces[i]);
    }
    
    momentForces.clear();
}


void Box::enableGravity()
{
    kmVec3 gravityForce = kmVec3Make(0.0, K_GRAVITY, 0.0);
    constantForces.push_back(gravityForce);
}

//triangle strip box representation
kmRect Box::getRect()
{
    kmRect rect;
    
    GLfloat hWidth = size.w/2.0;
    GLfloat hHeight = size.h/2.0;
    
    rect.bl = kmVec3Make(center.x - hWidth , center.y - hHeight, 0.0);
    rect.br = kmVec3Make(center.x + hWidth , center.y - hHeight, 0.0);
    rect.tl = kmVec3Make(center.x - hWidth , center.y + hHeight, 0.0);
    rect.tr = kmVec3Make(center.x + hWidth , center.y + hHeight, 0.0);
    
    return rect;
}


void Box::setVelocity(kmVec3 v)
{
    velocity = v;
}

kmVec3 Box::getCenter()
{
    return center;
}

kmSize Box::getSize(){
    return size;
}

void Box::applyImpulse(float force, kmVec3 direction)
{
    kmVec3 impulseForce = kmVec3Make(force * direction.x, force * direction.y, force * direction.z);
    momentForces.push_back(impulseForce);
}

kmVec3 Box::update(float dt)
{
    updateEndForce();
    
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

bool Box::intersect(Box* gameObject) {
    
    kmVec3 a = gameObject->getCenter();
    kmVec3 b = center;
    kmSize aSize = gameObject->getSize();
    kmSize bSize = size;
    
    return (abs(a.x - b.x) * 2 < (aSize.w + bSize.w)) &&
    (abs(a.y - b.y) * 2 < (aSize.h + bSize.h));
};

//
//  GBox.cpp
//  Flappy bird
//
//  Created by Ruben on 21/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#include "GBox.hpp"

#define K_GRAVITY 300.0

GBox::GBox(){};
GBox::GBox(kmVec3 _center, kmSize _size, int _shape /*SQUARE_SHAPE*/)
{
    shape = _shape;
    center = kmVec3Make(_center.x, _center.y, 0);
    
    size = kmSizeMake(_size.w, _size.h);
    
    velocity = kmVec3Make(0, 0, 0);
    mass = 1;
    
    isVisible = true;
    gravityEnabled = false;
    endForce = kmVec3Make(0, 0, 0);
}

kmRect GBox::getRect()
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

kmVec3 GBox::getCenter()
{
    return center;
}

kmSize GBox::getSize(){
    return size;
}

int GBox::getShape() {
    return shape;
}

void GBox::setVelocity(kmVec3 v)
{
    velocity = v;
}

void GBox::setCenter(kmVec3 c)
{
    center = c;
}

void GBox::updateEndForce()
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


void GBox::enableGravity()
{
    kmVec3 gravityForce = kmVec3Make(0.0, K_GRAVITY, 0.0);
    constantForces.push_back(gravityForce);
}

void GBox::applyImpulse(float force, kmVec3 direction)
{
    kmVec3 impulseForce = kmVec3Make(force * direction.x, force * direction.y, force * direction.z);
    momentForces.push_back(impulseForce);
}

kmVec3 GBox::update(float dt)
{
    updateEndForce();
    
    kmVec3 nextPosition = kmVec3Make(0, 0, 0);
    
    kmVec3 acceleration = kmVec3Make(endForce.x/mass, endForce.y/mass, endForce.z/mass);
    
    kmVec3 v = kmVec3Make(acceleration.x * dt, acceleration.y * dt, acceleration.z * dt);
    
    velocity = kmVec3Make(v.x + velocity.x, v.y + velocity.y, v.z + velocity.z);
    
    kmVec3 step = kmVec3Make(velocity.x * dt, velocity.y * dt, velocity.z * dt);
    nextPosition = kmVec3Make(center.x + step.x, center.y + step.y, center.z + step.z);
    setCenter(nextPosition);
    
    return nextPosition;
}

bool GBox::intersect(GBox* GObject) {
    
    bool intersect = false;
    if(GObject->getShape() == SQUARE_SHAPE &&
       shape == SQUARE_SHAPE) {
        kmVec3 a = GObject->getCenter();
        kmVec3 b = center;
        kmSize aSize = GObject->getSize();
        kmSize bSize = size;
        intersect = (abs(a.x - b.x)*2 < (aSize.w + bSize.w)) && (abs(a.y - b.y)*2 < (aSize.h + bSize.h));
    }
    else if (shape == SQUARE_SHAPE &&
             GObject->getShape() == CIRCULAR_SHAPE){
        intersect = true;
        kmSize circleSize = GObject->getSize();
        kmVec3 circleCenter = GObject->getCenter();
        kmSize rectSize = size;
        kmVec3 rectCenter = center;
        
        float circleDistanceX = abs(circleCenter.x - rectCenter.x);
        float circleDistanceY = abs(circleCenter.y - rectCenter.y);
        
        if (circleDistanceX > (rectSize.w/2.0 + circleSize.w/2.0)) { return false; }
        if (circleDistanceY > (rectSize.h/2.0 + circleSize.h/2.0)) { return false; }
        
        if (circleDistanceX <= (rectSize.w/2.0)) { return true; }
        if (circleDistanceY <= (rectSize.h/2.0)) { return true; }
        
        float cornerDistance_sq = pow((circleDistanceX - rectSize.w/2),2) +
        pow((circleDistanceY - rectSize.h/2),2);
        
        intersect = (cornerDistance_sq <= pow(circleSize.w/2.0,2));
    }
    return intersect;
};

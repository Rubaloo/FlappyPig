//
//  Box.hpp
//  Flappy bird
//
//  Created by Ruben on 21/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#ifndef Box_hpp
#define Box_hpp

#include <stdio.h>
#include "GTypes.hpp"
#include <vector>

using namespace std;

class Box {
public:
    Box();
    Box(kmVec3 center, kmSize size);
    
    bool moveTo(kmVec3 direction);
    bool intersect(Box* gameObject);
    
    kmRect getRect();
    kmVec3 getCenter();
    kmSize getSize();

    
    void setCenter(kmVec3 center);
    void setVelocity(kmVec3 velocity);
    
    
    kmVec3 update(float dt);
    
    void applyImpulse(float force, kmVec3 direction);
    void enableGravity();
    
private:
    GLfloat mass;
    kmVec3 center;
    kmSize size;
    //Physhcs
    vector<kmVec3> constantForces;
    vector<kmVec3> momentForces;
    kmVec3 velocity;
    kmVec3 direction;
    kmVec3 endForce;
    
    bool gravityEnabled;
    bool isVisible;
    
    void updateEndForce();
};

#endif /* Box_hpp */

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
    vector<kmVec3> getVertexs();
    kmVec3 getCenter();
    void setCenter(kmVec3 center);
    kmVec3 update(float dt);
    void applyImpulse(float force, kmVec3 direction);
    
private:
    GLfloat mass;
    kmVec3 center;
    kmSize size;
    //Physhcs
    kmVec3 velocity;
    kmVec3 direction;
    kmVec3 gravity;
    kmVec3 endForce;
    
    bool isVisible;
};

#endif /* Box_hpp */

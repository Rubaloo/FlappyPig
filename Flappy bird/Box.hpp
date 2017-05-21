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
    
private:
    GLfloat mass;
    kmVec3 center;
    kmSize size;
    kmVec3 direction;
    kmVec3 velocity;
    bool isVisible;
};

#endif /* Box_hpp */

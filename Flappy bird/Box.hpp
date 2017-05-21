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

class Box {
    
public:
    bool moveTo(kmVec3 direction);
    bool intersect(Box* gameObject);
    
private:
    float mass;
    kmVec3 direction;
    kmVec3 velocity;
    bool isVisible;
};

#endif /* Box_hpp */

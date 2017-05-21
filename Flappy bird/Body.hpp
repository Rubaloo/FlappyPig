//
//  Body.hpp
//  Flappy bird
//
//  Created by Ruben on 21/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#ifndef Body_hpp
#define Body_hpp

#include <stdio.h>
#include "GTypes.hpp"

class Body {
    
public:
    bool moveTo(kmVec3 direction);
    bool intersect(Body* gameObject);
    
private:
    float mass;
    kmVec3 direction;
    kmVec3 velocity;
    bool isVisible;
};





#endif /* Body_hpp */

//
//  Pipe.hpp
//  Flappy bird
//
//  Created by Ruben on 24/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#ifndef Pipe_hpp
#define Pipe_hpp

#include <stdio.h>
#include "GameObject.hpp"

class Pipe : public GameObject {
    
public:
    Pipe();
    Pipe(Box body);
    ~Pipe();
    
private:
    float height;
    void update(float dt);
    void render();
    
};
#endif /* Pipe_hpp */

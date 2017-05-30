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
#include "GObject.hpp"
#include "GTypes.hpp"

class Pipe : public GObject {
    
public:
    Pipe();
    Pipe(GBox body);
    ~Pipe();
    
    void update(float dt);
    void render();
};
#endif /* Pipe_hpp */

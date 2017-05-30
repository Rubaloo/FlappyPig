//
//  Bird.hpp
//  Flapi Pig
//
//  Created by Ruben on 13/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include <iostream>

#include "GObject.hpp"

class Bird : public GObject {
public:
    Bird();
    ~Bird();
    Bird(GBox body, int firstScore);
    int getShape();
    void jump();
    void render();
    void update(float dt);
    
private:
    
    int score;
};

#endif /* Player_hpp */

//
//  GameWorld.hpp
//  Flapi Pig
//
//  Created by Ruben on 13/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#ifndef GameWorld_hpp
#define GameWorld_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

#include "Renderer.hpp"

using namespace std;

class GameWorld {
private:
    float gravity;
    Renderer* painter;

    
public:
    GameWorld(float gravity);
    ~GameWorld();
    void render();
    
    //bool add(GameObject *gObject);
    //void update(float dt);
    //void initLevel();
};
#endif /* GameWorld_hpp */

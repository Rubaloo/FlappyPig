//
//  Player.hpp
//  Flapi Pig
//
//  Created by Ruben on 13/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include <iostream>

#include "GameObject.hpp"

class Player : public GameObject {
public:
    Player();
    Player(int score);
    ~Player();
    
private:
    void render();
    void update(float dt);
    void setGeometry();
    void setColor();
    int score;
};

#endif /* Player_hpp */

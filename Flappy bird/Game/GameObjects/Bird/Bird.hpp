#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include <iostream>

#include "GObject.hpp"

class Bird : public GObject {
public:
    Bird();
    Bird(GBox body);
    ~Bird();

    int getShape();
    
    void jump();
    void render();
    void update(float dt);
};

#endif /* Player_hpp */

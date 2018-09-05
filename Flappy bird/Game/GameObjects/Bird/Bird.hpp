#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include <iostream>

#include "GObject.hpp"

class Bird : public GObject
{
public:
    Bird(const GBox& aBody);
    
    int GetShape();
    
    void Jump();
    void Render();
    void Update(double dt);
};

#endif /* Player_hpp */

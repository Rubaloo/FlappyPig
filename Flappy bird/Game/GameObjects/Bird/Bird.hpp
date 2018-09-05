#ifndef Player_hpp
#define Player_hpp

#include "GObject.hpp"

class Bird : public GObject
{
public:
    Bird(const GBox& aBody);
    
    void Jump();
    void Render();
    void Update(double dt);
};

#endif /* Player_hpp */

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

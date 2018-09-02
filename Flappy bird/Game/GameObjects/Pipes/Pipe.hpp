#ifndef Pipe_hpp
#define Pipe_hpp

#include <stdio.h>
#include "GObject.hpp"
#include "GTypes.hpp"

class Pipe : public GObject {
    
public:
    Pipe(const GBox& body);
    
    void Update(double dt);
    void Render();
};
#endif /* Pipe_hpp */

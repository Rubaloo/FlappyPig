#ifndef Receiver_hpp
#define Receiver_hpp

#include <stdio.h>

class Receiver {
    
public:
    virtual void HandleInput(int i)=0;
};
#endif /* Receiver_hpp */

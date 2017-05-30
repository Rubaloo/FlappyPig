//
//  Receiver.hpp
//  Flappy bird
//
//  Created by Ruben on 24/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#ifndef Receiver_hpp
#define Receiver_hpp

#include <stdio.h>

class Receiver {
    
public:
    virtual void handleInput(int i)=0;
};
#endif /* Receiver_hpp */

//
//  PostMan.hpp
//  Flappy bird
//
//  Created by Ruben on 24/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#ifndef PostMan_hpp
#define PostMan_hpp

#include <stdio.h>
#include "Receiver.hpp"
#include <vector>

using namespace std;

class PostMan {
    
public:
    void send(int msg);
    void addReceiver(Receiver* receiver);
private:
    vector<Receiver*> receivers;
};

#endif /* PostMan_hpp */

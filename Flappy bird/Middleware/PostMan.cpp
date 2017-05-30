//
//  PostMan.cpp
//  Flappy bird
//
//  Created by Ruben on 24/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//
#include "PostMan.hpp"


void PostMan::addReceiver(Receiver* receiver) {
    receivers.push_back(receiver);
}

void PostMan::send(int msg)
{
    for(int i = 0; i < receivers.size(); ++i) {
        Receiver* r = receivers[i];
        r->handleInput(0);
    }
}

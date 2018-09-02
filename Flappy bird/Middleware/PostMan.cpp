#include "PostMan.hpp"


void PostMan::addReceiver(Receiver* receiver) {
    receivers.push_back(receiver);
}

void PostMan::send(int msg)
{
    for(int i = 0; i < receivers.size(); ++i) {
        Receiver* r = receivers[i];
        r->HandleInput(0);
    }
}

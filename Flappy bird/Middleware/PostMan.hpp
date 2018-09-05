#ifndef PostMan_hpp
#define PostMan_hpp

#include <stdio.h>
#include "Receiver.hpp"
#include <vector>

class PostMan
{
public:
    void Send(int msg);
    void AddReceiver(Receiver* receiver);
private:
    std::vector<Receiver*> mReceivers;
};

#endif /* PostMan_hpp */

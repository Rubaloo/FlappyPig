#include "PostMan.hpp"

using namespace std;

void PostMan::AddReceiver(Receiver* aReceiver)
{
    mReceivers.push_back(aReceiver);
}

void PostMan::Send(int aMsg)
{
    for_each(mReceivers.begin(), mReceivers.end(), [](Receiver* r){
        r->HandleInput(0);
    });
}

#include "PostMan.hpp"

using namespace std;

void PostMan::AddReceiver(Receiver* aReceiver) {
    mReceivers.push_back(aReceiver);
}

void PostMan::Send(int aMsg)
{
    for(int i = 0; i < mReceivers.size(); ++i) {
        Receiver* r = mReceivers[i];
        r->HandleInput(0);
    }
}

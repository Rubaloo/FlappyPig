#include "GDirector.hpp"


bool GDirector::instanceFlag = false;
GDirector* GDirector::single = NULL;

GDirector* GDirector::getInstance()
{
    if(! instanceFlag)
    {
        single = new GDirector();
        instanceFlag = true;
        return single;
    }
    else
    {
        return single;
    }
}

void GDirector::setWinSizeInPixels(kmSize deviceSize) {
    screenSize = deviceSize;
};

kmSize GDirector::getWinSizeInPixels() {
    return screenSize;
};

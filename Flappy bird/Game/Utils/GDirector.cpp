#include "GDirector.hpp"


bool GDirector::sInstanceFlag = false;
GDirector* GDirector::sSingle = NULL;

GDirector* GDirector::getInstance()
{
    if(! sInstanceFlag)
    {
        sSingle = new GDirector();
        sInstanceFlag = true;
        return sSingle;
    }
    else
    {
        return sSingle;
    }
}

void GDirector::SetWinSizeInPixels(const kmSize& aWinSize) {
    mScreenSize = aWinSize;
};

kmSize GDirector::GetWinSizeInPixels() {
    return mScreenSize;
};

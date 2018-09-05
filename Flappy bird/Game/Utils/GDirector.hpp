#ifndef GDirector_hpp
#define GDirector_hpp

#include <stdio.h>
#include "GTypes.hpp"

class GDirector
{
private:
    static bool sInstanceFlag;
    
    kmSize mScreenSize;
    static GDirector *sSingle;
    GDirector(){}
public:
    ~GDirector()
    {
        sInstanceFlag = false;
    }
    
    static GDirector* getInstance();
    
    kmSize GetWinSizeInPixels();
    void SetWinSizeInPixels(const kmSize& winSize);
};

#endif /* Director_hpp */

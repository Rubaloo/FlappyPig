#ifndef GDirector_hpp
#define GDirector_hpp

#include <stdio.h>
#include "GTypes.hpp"

#define KM_FALSE 0
#define KM_TRUE 1
#define VELOCITY_IDDLE kmVec3Make(0.0, 0.0, 0.0)
#define SCREEN_CENTER kmVec3Make(SCREEN_WIDTH/2.0, SCREEN_HEIGHT/2.0, 0.0)
#define SCREEN_SIZE kmSizeMake(SCREEN_WIDTH, SCREEN_HEIGHT)
#define SCREEN_WIDTH GDirector::getInstance()->GetWinSizeInPixels().w
#define SCREEN_HEIGHT GDirector::getInstance()->GetWinSizeInPixels().h
#define ASPECT_RATIO SCREEN_WIDTH/SCREEN_HEIGHT

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

//
//  Director.hpp
//  Flapi Pig
//
//  Created by Ruben on 18/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#ifndef GDirector_hpp
#define GDirector_hpp

#include <stdio.h>
#include "GTypes.hpp"


class GDirector
{
private:
    static bool instanceFlag;
    
    kmSize screenSize;
    static GDirector *single;
    GDirector(){}
public:
    ~GDirector()
    {
        instanceFlag = false;
    }
    
    static GDirector* getInstance();
    
    kmSize getWinSizeInPixels();
    void setWinSizeInPixels(kmSize winSize);
};

#endif /* Director_hpp */

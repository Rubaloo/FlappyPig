//
//  Director.cpp
//  Flapi Pig
//
//  Created by Ruben on 18/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

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

//
//  GameObject.cpp
//  Flapi Pig
//
//  Created by Ruben on 13/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#include "GameObject.hpp"

GameObject::GameObject(){}
GameObject::GameObject(Box b)
{
    body = b;
}

Box* GameObject::getBox()
{
    return &body;
}

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

bool GameObject::outsideLeftLimits()
{
    kmRect rect = body.getRect();
    kmSize size = body.getSize();
    return (rect.tl.x + size.w) < 0;
};

bool GameObject::intersect(GameObject* object)
{
    return body.intersect(object->getBox());
}

void GameObject::moveTo(kmVec3 translation)
{
    // System cordinates change
    GLfloat dx = (translation.x*ASPECT_RATIO)/SCREEN_WIDTH;
    GLfloat dy = (translation.y)/SCREEN_HEIGHT;
    GLfloat dz = 0.0;
    modelView.populateFromTranslation(kmVec3Make(dx, dy, dz));
}

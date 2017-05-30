//
//  GameObject.cpp
//  Flapi Pig
//
//  Created by Ruben on 13/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#include "GameObject.hpp"

GameObject::GameObject(){}
GameObject::GameObject(GBox b)
{
    body = b;
}

GBox* GameObject::getBox()
{
    return &body;
}

bool GameObject::outsideLeftLimits()
{
    kmRect rect = body.getRect();
    kmSize size = body.getSize();
    return (rect.tl.x + size.w) < 0;
};

bool GameObject::reachFloor() {
    return (body.getCenter().y + body.getSize().h/2.0) > SCREEN_HEIGHT;
};

bool GameObject::reachTop() {
    return (body.getCenter().y - body.getSize().h/2.0) < 0;
};

bool GameObject::intersect(GameObject* object)
{
    return body.intersect(object->getBox());
}

bool GameObject::intersect(GBox* GBox) {
    return body.intersect(GBox);
}

void GameObject::moveTo(kmVec3 translation)
{
    // System cordinates change
    modelView.addTranslation(translation);
}

void GameObject::resetModelView() {
    modelView.populateIdentity();
}

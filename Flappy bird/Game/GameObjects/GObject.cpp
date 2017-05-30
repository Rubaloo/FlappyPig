//
//  GObject.cpp
//  Flapi Pig
//
//  Created by Ruben on 13/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#include "GObject.hpp"

GObject::GObject(){}
GObject::GObject(GBox b)
{
    body = b;
}

GBox* GObject::getBox()
{
    return &body;
}

bool GObject::outsideLeftLimits()
{
    kmRect rect = body.getRect();
    kmSize size = body.getSize();
    return (rect.tl.x + size.w) < 0;
};

bool GObject::reachFloor() {
    return (body.getCenter().y + body.getSize().h/2.0) > SCREEN_HEIGHT;
};

bool GObject::reachTop() {
    return (body.getCenter().y - body.getSize().h/2.0) < 0;
};

bool GObject::intersect(GObject* object)
{
    return body.intersect(object->getBox());
}

void GObject::moveTo(kmVec3 translation)
{
    modelView.addTranslation(translation);
}

void GObject::resetModelView() {
    modelView.populateIdentity();
}

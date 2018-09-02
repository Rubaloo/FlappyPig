#include "GObject.hpp"

GObject::GObject(){}
GObject::GObject(GBox b)
{
    body = b;
}

GObject::~GObject()
{
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

void GObject::freeModelMesh()
{
    modelMesh.deleteBuffers();
}

bool GObject::intersect(GObject* object)
{
    return body.intersect(object->getBox());
}

void GObject::moveTo(kmVec3 translation)
{
    modelView.addTranslation(translation);
}

void GObject::moveBy(kmVec3 point)
{
    body.setCenter(point);
}

void GObject::resetModelView() {
    modelView.populateIdentity();
}

void GObject::update(float dt)
{
    cout << "Update method sould be implemented by GObject subclass" << endl;
}
    
void GObject::render()
{
    cout << "GObject::reder method should be implemented by subclass" << endl;
}

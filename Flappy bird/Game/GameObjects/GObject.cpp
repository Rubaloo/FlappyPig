#include "GObject.hpp"


GObject::GObject(){}
GObject::GObject(const GBox& aBox)
{
    mBody = aBox;
}

GObject::~GObject()
{
    mMmodelMesh.Unbind();
};

GBox& GObject::GetBox()
{
    return mBody;
}

bool GObject::OutsideLeftLimits()
{
    kmRect rect = mBody.GetRect();
    kmSize size = mBody.GetSize();
    return (rect.tl.x + size.w) < 0;
};

bool GObject::ReachFloor() {
    return (mBody.GetCenter().y + mBody.GetSize().h/2.0) > SCREEN_HEIGHT;
};

bool GObject::ReachTop() {
    return (mBody.GetCenter().y - mBody.GetSize().h/2.0) < 0;
};

void GObject::FreeModelMesh()
{
    mMmodelMesh.DeleteBuffers();
}

bool GObject::Intersect(const GObject& aObject)
{
    return mBody.Intersect(aObject.mBody);
}

void GObject::MoveBy(kmVec3 translation)
{
    mModelView.addTranslation(translation);
}

void GObject::MoveTo(kmVec3 point)
{
    mBody.SetCenter(point);
}

void GObject::ResetModelView() {
    mModelView.populateIdentity();
}

void GObject::Update(float dt)
{
    cout << "Update method sould be implemented by GObject subclass" << endl;
}
    
void GObject::Render()
{
    cout << "GObject::reder method should be implemented by subclass" << endl;
}

#include "GObject.hpp"
#include "GShader.hpp"
#include "GDirector.hpp"
#include "GTypes.hpp"
#include <iostream>

using namespace std;


GObject::GObject(const GBox& aBody) :
    mBody(aBody),
    mModelMesh(aBody),
    mModelView()
{}

GObject::~GObject()
{
    mModelMesh.Unbind();
}

GBox& GObject::GetBox()
{
    return mBody;
}

bool GObject::OutsideLeftLimits()
{
    kmRect rect = mBody.GetRect();
    kmSize size = mBody.GetSize();
    return (rect.tl.x + size.w) < 0;
}

bool GObject::ReachFloor()
{
    return (mBody.GetCenter().y + mBody.GetSize().h/2.0) > SCREEN_HEIGHT;
}

bool GObject::ReachTop()
{
    return (mBody.GetCenter().y - mBody.GetSize().h/2.0) < 0;
}

void GObject::FreeModelMesh()
{
    mModelMesh.DeleteBuffers();
}

bool GObject::Intersect(const GObject& aObject)
{
    return mBody.Intersect(aObject.mBody);
}

void GObject::MoveBy(kmVec3 translation)
{
    mModelView.AddTranslation(translation);
}

void GObject::MoveTo(kmVec3 point)
{
    mBody.SetCenter(point);
}

void GObject::ResetModelView() {
    mModelView.PopulateIdentity();
}

void GObject::Update(float dt)
{
    cout << "Update method sould be implemented by GObject subclass" << endl;
}
    
void GObject::Render()
{
    cout << "GObject::reder method should be implemented by subclass" << endl;
}

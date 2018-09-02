#include "GBox.hpp"

#define K_GRAVITY 800.0

GBox::GBox(kmVec3 aCenter, kmSize aSize, int aShape /*SQUARE_SHAPE*/)
    : mShape(aShape)
{
    mCenter = kmVec3Make(aCenter.x, aCenter.y, 0);
    
    mSize = kmSizeMake(aSize.w, aSize.h);
    
    velocity = kmVec3Make(0, 0, 0);
    mMass = 1;
    
    isVisible = true;
    gravityEnabled = false;
    endForce = kmVec3Make(0, 0, 0);
}

kmRect GBox::GetRect() const
{
    kmRect rect;
    
    GLfloat hWidth = mSize.w/2.0;
    GLfloat hHeight = mSize.h/2.0;
    
    rect.bl = kmVec3Make(mCenter.x - hWidth , mCenter.y - hHeight, 0.0);
    rect.br = kmVec3Make(mCenter.x + hWidth , mCenter.y - hHeight, 0.0);
    rect.tl = kmVec3Make(mCenter.x - hWidth , mCenter.y + hHeight, 0.0);
    rect.tr = kmVec3Make(mCenter.x + hWidth , mCenter.y + hHeight, 0.0);
    
    return rect;
}

kmVec3 GBox::GetCenter() const
{
    return mCenter;
}

kmSize GBox::GetSize() const
{
    return mSize;
}

int GBox::GetShape() const
{
    return mShape;
}

void GBox::SetVelocity(kmVec3 v)
{
    velocity = v;
}

void GBox::SetCenter(kmVec3 c)
{
    mCenter = c;
}

void GBox::updateEndForce()
{
    endForce = kmVec3Make(0,0,0);
    for(int i = 0; i < constantForces.size(); ++i) {
        endForce = kmVec3Add(endForce, constantForces[i]);
    }
    
    for(int i = 0; i < momentForces.size(); ++i) {
        endForce = kmVec3Add(endForce, momentForces[i]);
    }
    
    momentForces.clear();
}


void GBox::EnableGravity()
{
    kmVec3 gravityForce = kmVec3Make(0.0, K_GRAVITY, 0.0);
    constantForces.push_back(gravityForce);
}

void GBox::ApplyImpulse(float force, kmVec3 direction)
{
    kmVec3 impulseForce = kmVec3Make(force * direction.x, force * direction.y, force * direction.z);
    momentForces.push_back(impulseForce);
}

kmVec3 GBox::Update(double dt)
{
    updateEndForce();
    
    kmVec3 nextPosition = kmVec3Make(0, 0, 0);
    
    kmVec3 acceleration = kmVec3Make(endForce.x/mMass, endForce.y/mMass, endForce.z/mMass);
    
    kmVec3 v = kmVec3Make(acceleration.x * dt, acceleration.y * dt, acceleration.z * dt);
    
    velocity = kmVec3Make(v.x + velocity.x, v.y + velocity.y, v.z + velocity.z);
    
    kmVec3 step = kmVec3Make(velocity.x * dt, velocity.y * dt, velocity.z * dt);
    nextPosition = kmVec3Make(mCenter.x + step.x, mCenter.y + step.y, mCenter.z + step.z);
    SetCenter(nextPosition);
    
    return nextPosition;
}

bool GBox::Intersect(const GBox& aBox) const
{
    
    bool intersect = false;
    if(aBox.GetShape() == SQUARE_SHAPE && mShape == SQUARE_SHAPE)
    {
        kmVec3 a = aBox.GetCenter();
        kmVec3 b = mCenter;
        kmSize aSize = aBox.GetSize();
        kmSize bSize = mSize;
        intersect = (abs(a.x - b.x)*2 < (aSize.w + bSize.w)) && (abs(a.y - b.y)*2 < (aSize.h + bSize.h));
    }
    else if (mShape == SQUARE_SHAPE &&
             aBox.GetShape() == CIRCULAR_SHAPE)
    {
        kmSize circleSize = aBox.GetSize();
        kmVec3 circleCenter = aBox.GetCenter();
        kmSize rectSize = mSize;
        kmVec3 rectCenter = mCenter;
        
        float circleDistanceX = abs(circleCenter.x - rectCenter.x);
        float circleDistanceY = abs(circleCenter.y - rectCenter.y);
        
        if (circleDistanceX > (rectSize.w/2.0 + circleSize.w/2.0)) { return false; }
        if (circleDistanceY > (rectSize.h/2.0 + circleSize.h/2.0)) { return false; }
        
        if (circleDistanceX <= (rectSize.w/2.0)) { return true; }
        if (circleDistanceY <= (rectSize.h/2.0)) { return true; }
        
        float cornerDistance_sq = pow((circleDistanceX - rectSize.w/2),2) +
        pow((circleDistanceY - rectSize.h/2),2);
        
        intersect = (cornerDistance_sq <= pow(circleSize.w/2.0,2));
    }
    return intersect;
};

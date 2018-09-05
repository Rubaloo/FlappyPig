#ifndef Box_hpp
#define Box_hpp

#include <stdio.h>
#include <vector>
#include <cmath>
#include "GDirector.hpp"
#include "GTypes.hpp"

#define SQUARE_SHAPE 0
#define CIRCULAR_SHAPE 1

class GBox
{
public:
    GBox(kmVec3 aCenter, kmSize aSize, int aShape=SQUARE_SHAPE);
   
    int GetShape() const;
    kmRect GetRect() const;
    kmVec3 GetCenter() const;
    kmSize GetSize() const;

    void SetCenter(kmVec3 aCenter);
    void SetVelocity(kmVec3 aVelocity);
    
    kmVec3 Update(double dt);
    bool Intersect(const GBox& aBox) const;
    void ApplyImpulse(float aForce, kmVec3 aDirection);
    void EnableGravity();
    
private:
    GLfloat mMass;
    kmVec3 mCenter;
    kmSize mSize;
    
    //Physhics
    int mShape;
    std::vector<kmVec3> mConstantForces;
    std::vector<kmVec3> mMomentForces;
    kmVec3 mVelocity;
    kmVec3 mDirection;
    kmVec3 mEndForce;
    bool mGravityEnabled;
    bool mIsVisible;
    
    void UpdateEndForce();
};

#endif /* Box_hpp */

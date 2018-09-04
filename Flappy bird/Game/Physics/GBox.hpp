#ifndef Box_hpp
#define Box_hpp

#include <stdio.h>
#include "GTypes.hpp"
#include <vector>
#include "GDirector.hpp"
#include <cmath>

#define SQUARE_SHAPE 0
#define CIRCULAR_SHAPE 1

using namespace std;

class GBox {
public:
    GBox();
    GBox(kmVec3 aCenter, kmSize aSize, int aShape=SQUARE_SHAPE);
    int mShape;
    
    bool Intersect(const GBox& aBox) const;
    
    int GetShape() const;
    kmRect GetRect() const;
    kmVec3 GetCenter() const;
    kmSize GetSize() const;

    
    void SetCenter(kmVec3 aCenter);
    void SetVelocity(kmVec3 aVelocity);
    
    
    kmVec3 Update(double dt);
    
    void ApplyImpulse(float force, kmVec3 direction);
    void EnableGravity();
    
private:
    GLfloat mMass;
    kmVec3 mCenter;
    kmSize mSize;
    //Physhcs
    vector<kmVec3> constantForces;
    vector<kmVec3> momentForces;
    kmVec3 mVelocity;
    kmVec3 mDirection;
    kmVec3 mEndForce;
    
    bool mGravityEnabled;
    bool mIsVisible;
    
    void UpdateEndForce();
};

#endif /* Box_hpp */

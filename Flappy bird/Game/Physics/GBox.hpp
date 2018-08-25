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
    GBox(kmVec3 center, kmSize size, int shape=SQUARE_SHAPE);
    
    int shape;
    bool intersect(GBox* GObject);
    
    int getShape();
    kmRect getRect();
    kmVec3 getCenter();
    kmSize getSize();

    
    void setCenter(kmVec3 center);
    void setVelocity(kmVec3 velocity);
    
    
    kmVec3 update(float dt);
    
    void applyImpulse(float force, kmVec3 direction);
    void enableGravity();
    
private:
    GLfloat mass;
    kmVec3 center;
    kmSize size;
    //Physhcs
    vector<kmVec3> constantForces;
    vector<kmVec3> momentForces;
    kmVec3 velocity;
    kmVec3 direction;
    kmVec3 endForce;
    
    bool gravityEnabled;
    bool isVisible;
    
    void updateEndForce();
};

#endif /* Box_hpp */

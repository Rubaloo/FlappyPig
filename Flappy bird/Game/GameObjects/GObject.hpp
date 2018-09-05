#ifndef GameObject_hpp
#define GameObject_hpp

#include <iostream>
#include <stdio.h>
#include <vector>
#include <OpenGLES/ES2/gl.h>

//Forward declaration
class GBox;

#include "GVertexArray.hpp"
#include "GLMatrix.hpp"


class GObject
{
protected:
    GBox mBody;
    GVertexArray mModelMesh;
    GLMatrix mModelView;
public:
    GObject();
    GObject(const GBox& aBox);
    ~GObject();
    
    GBox& GetBox();
    
    void MoveTo(kmVec3 point);
    void MoveBy(kmVec3 translation);
    void ResetModelView();
    void FreeModelMesh();
    
    bool Intersect(const GObject& object);
    bool ReachTop();
    bool ReachFloor();
    bool OutsideLeftLimits();
    
    void Update(float dt);
    void Render();
};
#endif /* GameObject_hpp */

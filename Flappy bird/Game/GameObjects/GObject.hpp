#ifndef GameObject_hpp
#define GameObject_hpp

#include <iostream>
#include <stdio.h>
#include <vector>
#include <OpenGLES/ES2/gl.h>
#include "GLMatrix.hpp"
#include "GDirector.hpp"
#include "GTypes.hpp"
#include "GLVertex.hpp"
#include "GBox.hpp"
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

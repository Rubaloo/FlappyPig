#ifndef GameObject_hpp
#define GameObject_hpp

//Forward declaration
struct kmVec3;

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

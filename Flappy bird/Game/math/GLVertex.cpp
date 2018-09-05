#include "GLVertex.hpp"


GLVertex::GLVertex(kmVec3 aPosition, kmVec4 aColor)
{
    Populate(aPosition, aColor);
}

glVertex GLVertex::glVertex()
{
    return mVertex;
}

void GLVertex::Populate(kmVec3 gPosition, kmVec4 gColor) {
    mVertex.position[0] = gPosition.x;
    mVertex.position[1] = gPosition.y;
    mVertex.position[2] = gPosition.z;
    
    mVertex.color[0] = gColor.x;
    mVertex.color[1] = gColor.y;
    mVertex.color[2] = gColor.z;
    mVertex.color[3] = gColor.w;
};

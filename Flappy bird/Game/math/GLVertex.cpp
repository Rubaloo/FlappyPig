#include "GLVertex.hpp"


GLVertex::GLVertex(kmVec3 position, kmVec4 color) {
    populate(position, color);
}

glVertex GLVertex::glVertex()
{
    return vertex;
}

void GLVertex::populate(kmVec3 gPosition, kmVec4 gColor) {
    vertex.position[0] = gPosition.x;
    vertex.position[1] = gPosition.y;
    vertex.position[2] = gPosition.z;
    
    vertex.color[0] = gColor.x;
    vertex.color[1] = gColor.y;
    vertex.color[2] = gColor.z;
    vertex.color[3] = gColor.w;
};

#ifndef GLVertex_hpp
#define GLVertex_hpp

#include <stdio.h>
#include <OpenGLES/ES2/gl.h>
#include "GTypes.hpp"




class GLVertex {
    
public:
    GLVertex(kmVec3 position, kmVec4 color);
    glVertex glVertex();
    void populate(kmVec3 position, kmVec4 color);
    
private:
    struct glVertex vertex;
    GLfloat position[2];
    GLfloat color[4];
};

#endif /* GLVertex_hpp */

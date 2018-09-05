#ifndef GLVertex_hpp
#define GLVertex_hpp

#include <OpenGLES/ES2/gl.h>
#include "GTypes.hpp"

class GLVertex
{
public:
    GLVertex(kmVec3 aPosition, kmVec4 aColor);
    glVertex glVertex();
    void Populate(kmVec3 aPosition, kmVec4 aColor);
    
private:
    struct glVertex mVertex;
    GLfloat mPosition[2];
    GLfloat mColor[4];
};

#endif /* GLVertex_hpp */

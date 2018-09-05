#ifndef VertexArray_hpp
#define VertexArray_hpp

#include <stdio.h>
#include "GTypes.hpp"

#include <OpenGLES/ES2/gl.h>

class GBox;

class GVertexArray
{
public:
    GVertexArray(const GBox& aBody);
    
    void DeleteBuffers();
    void Bind();
    void Unbind();
    void Draw();
    void Render();
private:
    GLuint mVbo, mIbo;
    GLuint mIndexCount;
    
};
#endif /* VertexArray_hpp */

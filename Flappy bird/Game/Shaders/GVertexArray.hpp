#ifndef VertexArray_hpp
#define VertexArray_hpp

#include <stdio.h>
#include "GTypes.hpp"
#include "GShader.hpp"
#include <OpenGLES/ES2/gl.h>
#include "GBox.hpp"

class GVertexArray
{    
public:
    GVertexArray();
    GVertexArray(const GBox& aBody);
    GVertexArray(glVertex aVertexs[], GLubyte aIndexs[]);
    ~GVertexArray();
    
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

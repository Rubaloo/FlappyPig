#ifndef VertexArray_hpp
#define VertexArray_hpp

#include <stdio.h>
#include "GTypes.hpp"
#include "GShader.hpp"
#include <OpenGLES/ES2/gl.h>
class GVertexArray {
    
public:
    GVertexArray();
    GVertexArray(glVertex vertexs[], GLubyte indexs[]);
    
    void deleteBuffers();
    void bind();
    void unbind();
    void draw();
    void render();
private:
    GLuint vao, vbo, ibo, tbo;
    GLuint indexCount;
    
};
#endif /* VertexArray_hpp */

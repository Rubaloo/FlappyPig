#ifndef GShader_hpp
#define GShader_hpp

#include <stdio.h>
#include <iostream>
#include "GTypes.hpp"
#include "GShaderUtils.hpp"

#include <OpenGLES/ES2/gl.h>

static const GLuint GSHADER_VERTEX_ATTRIB = 0;
static const GLuint GSHADER_COLOR_ATTRIB = 1;

class GShader
{
    
public:
    GShader(const char* aVertexName, const char* aFragmentName);
    
    static GShader* BIRD;
    static GShader* PIPE;
    static void LoadAll();
    
    GLuint GetUniform(const char* aName);
    GLuint GetAttribute(const char* aName);
    GLuint GetID();
    
    void SetUniform1f(const char* aName, GLfloat f);
    void SetUniform2f(const char* aName, GLfloat x, GLfloat y);
    void SetUniform3f(const char* aName, kmVec3 vector);
    void SetUniform4f(const char* aName, GLfloat* matrix);
    
    void EnableVertexAttribute(const char* aName);
    void Enable();
    void Disable();
    
private:
    bool mEnabled;
    GLuint mID;
    
};
#endif /* GShader_hpp */

//
//  GShader.hpp
//  Flappy bird
//
//  Created by Ruben on 22/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#ifndef GShader_hpp
#define GShader_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include "GTypes.hpp"
#include "GShaderUtils.hpp"

#include <OpenGLES/ES2/gl.h>

using namespace std;

static const GLuint GSHADER_VERTEX_ATTRIB = 0;
static const GLuint GSHADER_COLOR_ATTRIB = 1;


class GShader {
public:
    GShader(string vertex, string fragment);
    
    static GShader* BIRD;
    static GShader* PIPE;
    static void loadAll();
    
    GLuint getUniform(string name);
    GLuint getAttribute(string name);
    GLuint getID();
    
    void setUniform1f(string name, GLfloat f);
    void setUniform2f(string name, GLfloat x, GLfloat y);
    void setUniform3f(string name, kmVec3 vector);
    void setUniform4f(string name, GLfloat* matrix);
    
    void enableVertexAttribute(string name);
    void enable();
    void disable();
    
private:
    bool enabled;
    GLuint ID;
    
};
#endif /* GShader_hpp */

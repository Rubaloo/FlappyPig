//
//  VertexArray.hpp
//  Flappy bird
//
//  Created by Ruben on 22/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#ifndef VertexArray_hpp
#define VertexArray_hpp

#include <stdio.h>
#include "GTypes.hpp"
#include "GShader.hpp"
#include <OpenGLES/ES2/gl.h>
class VertexArray {
    
public:
    VertexArray();
    VertexArray(glVertex vertexs[], GLbyte indexs[]);
    void bind();
    void unbind();
    void draw();
    void render();
private:
    GLuint vao, vbo, ibo, tbo;
    GLuint indexCount;
    
};
#endif /* VertexArray_hpp */

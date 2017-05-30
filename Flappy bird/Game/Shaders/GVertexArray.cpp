//
//  GVertexArray.cpp
//  Flappy bird
//
//  Created by Ruben on 22/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#include "GVertexArray.hpp"


GVertexArray::GVertexArray() {}
GVertexArray::GVertexArray(glVertex vertexs[4], GLubyte indexs[4]){
    
    const glVertex Vertices[] = {
        {vertexs[0]},
        {vertexs[1]},
        {vertexs[2]},
        {vertexs[3]}
    };
    
    const GLubyte Indices[] = {
        indexs[0], indexs[1], indexs[2], indexs[3]
    };
    
    indexCount = sizeof(Indices);
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GVertexArray::bind(){
    if(ibo > 0 && vbo > 0) {
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    }
}
void GVertexArray::unbind(){
    if(ibo > 0 && vbo > 0) {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}
void GVertexArray::draw(){
    if(ibo > 0) {
        glVertexAttribPointer(GSHADER_VERTEX_ATTRIB, 3, GL_FLOAT, GL_FALSE, sizeof(glVertex), (void *)offsetof(glVertex, position));
        glVertexAttribPointer(GSHADER_COLOR_ATTRIB, 4, GL_FLOAT, GL_FALSE, sizeof(glVertex), (void *)offsetof(glVertex, color));
        glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_BYTE, 0);
    }
}
void GVertexArray::render(){
    bind();
    draw();
}

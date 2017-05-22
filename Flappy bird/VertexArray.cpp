//
//  VertexArray.cpp
//  Flappy bird
//
//  Created by Ruben on 22/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#include "VertexArray.hpp"


VertexArray::VertexArray() {}
VertexArray::VertexArray(glVertex vertexs[], GLubyte indexs[]){
    indexCount = sizeof(indexs);
//    vao = glGenVertexArrays();
    //glBindVertexArray(vao);
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glVertex), vertexs, GL_STATIC_DRAW);
    glVertexAttribPointer(GSHADER_VERTEX_ATTRIB, 3, GL_FLOAT, GL_FALSE, sizeof(glVertex), (void *)offsetof(glVertex, position));
    glVertexAttribPointer(GSHADER_COLOR_ATTRIB, 4, GL_FLOAT, GL_FALSE, sizeof(glVertex), (void *)offsetof(glVertex, color));
    
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexs), indexs, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindVertexArray(0);
}

void VertexArray::bind(){
    if(ibo > 0) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    }
}
void VertexArray::unbind(){
    if(ibo > 0) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}
void VertexArray::draw(){
    if(ibo > 0) {
        glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_BYTE, 0);
    }
}
void VertexArray::render(){
    bind();
    draw();
}

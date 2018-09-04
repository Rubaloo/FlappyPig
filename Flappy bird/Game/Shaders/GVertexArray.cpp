#include "GVertexArray.hpp"

GVertexArray::GVertexArray(){};
GVertexArray::GVertexArray(glVertex aVertexs[4], GLubyte aIndexs[4])
{
    const glVertex Vertices[] = {
        {aVertexs[0]}, {aVertexs[1]}, {aVertexs[2]}, {aVertexs[3]}
    };
    
    const GLubyte Indices[] = {
        aIndexs[0], aIndexs[1], aIndexs[2], aIndexs[3]
    };
    
    mIndexCount = sizeof(Indices);
    
    glGenBuffers(1, &mVbo);
    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &mIbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GVertexArray::~GVertexArray(){}

void GVertexArray::Bind()
{
    if(mIbo > 0 && mVbo > 0) {
        glBindBuffer(GL_ARRAY_BUFFER, mVbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIbo);
    }
}
void GVertexArray::Unbind()
{
    if(mIbo > 0 && mVbo > 0) {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}
void GVertexArray::Draw()
{
    if(mVbo > 0 && mIbo > 0)
    {
        glVertexAttribPointer(GSHADER_VERTEX_ATTRIB, 3, GL_FLOAT, GL_FALSE, sizeof(glVertex), (void *)offsetof(glVertex, position));
        glVertexAttribPointer(GSHADER_COLOR_ATTRIB, 4, GL_FLOAT, GL_FALSE, sizeof(glVertex), (void *)offsetof(glVertex, color));
        glDrawElements(GL_TRIANGLE_STRIP, mIndexCount, GL_UNSIGNED_BYTE, 0);
    }
}

void GVertexArray::DeleteBuffers()
{
    glDeleteBuffers(1, &mVbo);
    glDeleteBuffers(1, &mIbo);
}

void GVertexArray::Render(){
    Bind();
    Draw();
}

#include "GVertexArray.hpp"

GVertexArray::GVertexArray(glVertex vertexs[4], GLubyte indexs[4])
{
    const glVertex Vertices[] = {
        {vertexs[0]},
        {vertexs[1]},
        {vertexs[2]},
        {vertexs[3]}
    };
    
    const GLubyte Indices[] = {
        indexs[0], indexs[1], indexs[2], indexs[3]
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

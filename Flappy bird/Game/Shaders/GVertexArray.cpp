#include "GVertexArray.hpp"
#include "GDirector.hpp"

GVertexArray::GVertexArray() = default;
GVertexArray::GVertexArray(const GBox& aBody)
{
    kmSize size = aBody.GetSize();
    
    GLfloat w = (size.w*ASPECT_RATIO)/SCREEN_WIDTH;
    GLfloat h = size.h/SCREEN_HEIGHT;
    
    GLfloat h2 = h/2.0;
    GLfloat w2 = w/2.0;
    
    
    glVertex modelVertexs[] = {
        {{-w2, h2, 0},{1,0,0,1}},
        {{w2, h2, 0},{0,1,0,1}},
        {{-w2, -h2, 0},{0,0,1,1}},
        {{w2,-h2, 0},{1,0,0,1}}
    };
    
    GLubyte modelIndexs[] = {0,1,2,3};
    
    const glVertex Vertices[] = {
        {modelVertexs[0]}, {modelVertexs[1]}, {modelVertexs[2]}, {modelVertexs[3]}
    };
    
    const GLubyte Indices[] = {
        modelIndexs[0], modelIndexs[1], modelIndexs[2], modelIndexs[3]
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
GVertexArray::GVertexArray(glVertex aVertexs[4], GLubyte aIndexs[4])
{
  
}

GVertexArray::~GVertexArray() = default;

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

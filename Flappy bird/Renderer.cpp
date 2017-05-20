//
//  Renderer.cpp
//  Flapi Pig
//
//  Created by Ruben on 17/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#include "Renderer.hpp"
#include <vector>
#import "GTypes.hpp"
#import "GLMatrix.hpp"
#import "GDirector.hpp"
#import "GLVertex.hpp"

#define VERTEX_SHADER_NAME "SimpleVertex"
#define FRAGMENT_SHADER_NAME "SimpleFragment"

typedef struct {
    float Position[3];
    float Color[4];
} Vertex;

const Vertex Vertices[] = {
    {{0, 0, 0}, {1, 0, 0, 1}},
    {{0.5, 0, 0}, {0, 1, 0, 1}},
    {{0.5, 0.5, 0}, {0, 0, 1, 1}},
    {{0, 0.5, 0}, {0, 0, 1, 1}}
};
 
const GLubyte Indices[] = {
    0, 1, 3, 2
};

void Renderer::setupRenderContext()
{
    setupVBO();
    loadShader();
}
void Renderer::setupVBO()
{
    // setup VBO
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

}

void Renderer::loadShader()
{
    //Compile Shaders
    pipeline = new Shader(VERTEX_SHADER_NAME, FRAGMENT_SHADER_NAME);
    
    if(!pipeline->compileAndLink()) {
        printf("Encountered problems when loading shader, application will crash...");
    }
    else {
        GLuint shaderProgram = pipeline->getProgram();
        glUseProgram(shaderProgram);
        
        //EnableAttributtes
        positionSlot = glGetAttribLocation(shaderProgram, "Position");
        colorSlot = glGetAttribLocation(shaderProgram, "SourceColor");
        modelViewUniform = glGetUniformLocation(shaderProgram, "ModelView");
        projectionUniform = glGetUniformLocation(shaderProgram, "Projection");
        
        //check that the locations are valid, negative value means invalid
        if(positionSlot < 0 || colorSlot < 0 ||
           modelViewUniform < 0  || projectionUniform < 0)
        {
            printf("Could not query attribute locations");
        }
        
        glEnableVertexAttribArray(positionSlot);
        glEnableVertexAttribArray(colorSlot);
    }

}

void Renderer::render()
{
    vector<glVertex> vertexs;
    vector<GLubyte> indexs;
    
    kmSize screenSize = GDirector::getInstance()->getWinSizeInPixels();
    
    kmGLVec4 red = kmGLVec4Make(1.0, 0.0, 0.0, 1.0);
    kmGLVec4 blue = kmGLVec4Make(0.0, 0.0, 1.0, 1.0);
    kmGLVec4 green = kmGLVec4Make(0.0, 1.0, 0.0, 1.0);
    
    
    GLVertex gv1(kmGLVec3Make(0.0, 0.0, 0.0), red);
    GLVertex gv2(kmGLVec3Make(0.0, screenSize.w/2.0, 0.0),blue);
    GLVertex gv3(kmGLVec3Make(screenSize.h/2.0, screenSize.w/2.0, 0.0), green);
    GLVertex gv4(kmGLVec3Make(screenSize.h/2.0, 0.0, 0.0),red);
    
    vertexs.push_back(gv1.glVertex());
    vertexs.push_back(gv2.glVertex());
    vertexs.push_back(gv3.glVertex());
    vertexs.push_back(gv4.glVertex());

    
    glClearColor(0, 104.0/255.0, 55.0/255.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    GLMatrix projection;
    projection.populateOrtho(-1, 1, -1, 1, -1, 1);
    glUniformMatrix4fv(projectionUniform, 1, 0, projection.matrix());
    
    GLMatrix modelView;
    modelView.populateFromTranslation(kmVec3Make(0, 0, 0));
    glUniformMatrix4fv(projectionUniform, 1, 0, projection.matrix());
    glUniformMatrix4fv(modelViewUniform, 1, 0, modelView.matrix());

    // 1
    glViewport(0, 0, screenSize.w, screenSize.h);
    
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    
    // 2
    glVertexAttribPointer(positionSlot, 3, GL_FLOAT, GL_FALSE, sizeof(vertexs), (GLvoid *)offsetof(glVertex, position));
    glVertexAttribPointer(colorSlot, 4, GL_FLOAT, GL_FALSE, sizeof(vertexs), (GLvoid *)offsetof(glVertex, color));
    
    // 3
    glDrawElements(GL_TRIANGLE_STRIP, sizeof(indexs)/sizeof(GLubyte), GL_UNSIGNED_BYTE, 0);
}







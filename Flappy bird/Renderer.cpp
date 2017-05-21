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
    
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
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

void Renderer::render(vector<GameObject*> objects)
{
    vector<glVertex> vertexs;
    vector<GLubyte> indexs;

    
    for(int i = 0; i < objects.size(); ++i) {
        GameObject* object = objects[i];
//        if(i > 0) {
//            glVertex start = vertexs[vertexs.size()-1];
//            glVertex end = vertexs[vertexs.size()-1];
//            addDegenerateTriangles(start, end);
//        }
        vector<glVertex>* objectVertexs = object->getVertexs();
        vertexs.insert(vertexs.end(), objectVertexs->begin(), objectVertexs->end());
        vector<GLubyte>* objectIndexs = object->getIndexs();
        indexs.insert(indexs.end(), objectIndexs->begin(), objectIndexs->end());
    }
    
    kmSize screenSize = GDirector::getInstance()->getWinSizeInPixels();
    
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
    glBufferData(GL_ARRAY_BUFFER, vertexs.size() * sizeof(glVertex), &vertexs[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexs.size() * sizeof(GLubyte), &indexs[0], GL_STATIC_DRAW);

    
    // 2
    glVertexAttribPointer(positionSlot, 3, GL_FLOAT, GL_FALSE, sizeof(glVertex), (void *)offsetof(glVertex, position));
    glVertexAttribPointer(colorSlot, 4, GL_FLOAT, GL_FALSE, sizeof(glVertex), (void *)offsetof(glVertex, color));
    
    // 3
    glDrawElements(GL_TRIANGLE_STRIP, indexs.size(), GL_UNSIGNED_BYTE, 0);
}







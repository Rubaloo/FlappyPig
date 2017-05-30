//
//  Pipe.cpp
//  Flappy bird
//
//  Created by Ruben on 24/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#include "Pipe.hpp"

Pipe::Pipe() : GObject(){}
Pipe::Pipe(GBox body) :GObject(body)
{
    kmSize size = body.getSize();
    
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

    modelView.populateIdentity();
    move(body.getCenter());
    GLubyte modelIndexs[] = {0,1,2,3};
    modelMesh = new GVertexArray(modelVertexs, modelIndexs);
}

Pipe::~Pipe(){};

void Pipe::update(float dt)
{
    kmVec3 nextPosition = body.update(dt);
    kmVec3 translation = modelView.getTranslation();
    body.setCenter(kmVec3Add(translation, body.getCenter()));
    moveTo(nextPosition);
}

void Pipe::render() {
    
    GLMatrix projection;
    projection.populateOrtho(0, ASPECT_RATIO, 1, 0, -1, 1);
    
    GShader::PIPE->enable();
    GShader::PIPE->enableVertexAttribute("Position");
    GShader::PIPE->enableVertexAttribute("SourceColor");
    
    kmMat4 gMatrix;
    modelView.gMatrix(&gMatrix);
    GShader::PIPE->setUniform4f("ModelView", gMatrix.mat);
    
    GShader::PIPE->setUniform4f("Projection", projection.matrix());
    modelMesh->render();
    resetModelView();
    GShader::PIPE->disable();
    
    
};

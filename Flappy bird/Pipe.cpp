//
//  Pipe.cpp
//  Flappy bird
//
//  Created by Ruben on 24/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#include "Pipe.hpp"

#include "GameObject.hpp"

Pipe::Pipe() : GameObject(){}
Pipe::Pipe(Box body) : GameObject(body)
{
    kmSize bodySize = body.getSize();
    
    glVertex modelVertexs[] = {
        {{0.0, bodySize.h, 0.0},{1,0,0,1}},
        {{bodySize.w, bodySize.h, 0.0},{0,1,0,1}},
        {{0.0, 0.0, 0.0},{0,0,1,1}},
        {{0.0, bodySize.w, 0},{1,0,0,1}}
    };
    modelView.populateFromTranslation(body.getCenter());
    GLubyte modelIndexs[] = {0,1,2,3};
    modelMesh = new VertexArray(modelVertexs, modelIndexs);
}

Pipe::~Pipe(){};

int i = 0;
void Pipe::update(float dt)
{
    //kmVec3 nextPosition = body.update(dt);
    //modelView.populateFromTranslation(nextPosition);
}

void Pipe::render() {
    
    GLMatrix projection;
    projection.populateOrtho(-1, 1, -1, 1, -1, 1);
    
    GShader::BIRD->enable();
    GShader::BIRD->enableVertexAttribute("Position");
    GShader::BIRD->enableVertexAttribute("SourceColor");
    GShader::BIRD->setUniform4f("ModelView", modelView.matrix());
    GShader::BIRD->setUniform4f("Projection", projection.matrix());
    modelMesh->render();
    GShader::BIRD->disable();
    
    
};

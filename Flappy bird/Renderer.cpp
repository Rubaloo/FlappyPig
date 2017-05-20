//
//  Renderer.cpp
//  Flapi Pig
//
//  Created by Ruben on 17/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#include "Renderer.hpp"
#define VERTEX_SHADER_NAME "SimpleVertex"
#define FRAGMENT_SHADER_NAME "SimpleFragment"

typedef struct {
    float Position[3];
    float Color[4];
} Vertex;

const Vertex Vertices[] = {
    {{0, 0, 0}, {1, 0, 0, 1}},
    {{1, 0, 0}, {0, 1, 0, 1}},
    {{1, 1, 0}, {0, 0, 1, 1}}
};
 
const GLubyte Indices[] = {
    0, 1, 2
};

void Renderer::setupRenderContext()
{
    int p;
}

void Renderer::render()
{
    
}







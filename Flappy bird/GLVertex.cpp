//
//  GLVertex.cpp
//  Flapi Pig
//
//  Created by Ruben on 18/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#include "GLVertex.hpp"


GLVertex::GLVertex(kmGLVec3 position, kmGLVec4 color) {
    populate(position, color);
}

glVertex GLVertex::glVertex()
{
    return vertex;
}

void GLVertex::populate(kmGLVec3 gPosition, kmGLVec4 gColor) {
    vertex.position[0] = gPosition.x;
    vertex.position[1] = gPosition.y;
    vertex.position[2] = gPosition.z;
    
    vertex.color[0] = gColor.x;
    vertex.color[1] = gColor.y;
    vertex.color[2] = gColor.z;
    vertex.color[3] = gColor.w;
};

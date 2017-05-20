//
//  GLVertex.hpp
//  Flapi Pig
//
//  Created by Ruben on 18/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#ifndef GLVertex_hpp
#define GLVertex_hpp

#include <stdio.h>
#include <OpenGLES/ES2/gl.h>
#include "GTypes.hpp"


typedef struct glVertex {
    GLfloat position[3];
    GLfloat color[4];
} glVertex;

class GLVertex {
    
public:
    GLVertex(kmGLVec3 position, kmGLVec4 color);
    glVertex glVertex();
    void populate(kmGLVec3 position, kmGLVec4 color);
    
private:
    struct glVertex vertex;
    GLfloat position[2];
    GLfloat color[4];
};

#endif /* GLVertex_hpp */

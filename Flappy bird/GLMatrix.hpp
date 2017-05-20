//
//  GLMatrix.hpp
//  Flapi Pig
//
//  Created by Ruben on 17/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#ifndef GLMatrix_hpp
#define GLMatrix_hpp

#include <string>
#include <stdio.h>
#include <OpenGLES/ES2/gl.h>
#include "GTypes.hpp"

class GLMatrix {

public:
    GLfloat* matrix();
    void populateOrtho(GLfloat left,
                       GLfloat right,
                       GLfloat bottom,
                       GLfloat top,
                       GLfloat near,
                       GLfloat far);
    
    void populateFromTranslation(kmVec3 translation);
    
private:
    kmMat4 glMatrix;
    void populateIdentity();
};


#endif /* GLMatrix_hpp */

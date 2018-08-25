#ifndef GLMatrix_hpp
#define GLMatrix_hpp

#include <string>
#include <stdio.h>
#include <OpenGLES/ES2/gl.h>
#include "GDirector.hpp"
#include "GTypes.hpp"

class GLMatrix {

public:
    GLfloat* matrix();
    void gMatrix(kmMat4* mat);
    void populateOrtho(GLfloat left,
                       GLfloat right,
                       GLfloat bottom,
                       GLfloat top,
                       GLfloat near,
                       GLfloat far);
    
    void populateFromTranslation(kmVec3 translation);
    void addTranslation(kmVec3 translation);
    kmVec3 getTranslation();
    
    void populateIdentity();
    
private:
    bool initialized = false;
    kmMat4 glMatrix;
};


#endif /* GLMatrix_hpp */

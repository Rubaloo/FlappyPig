#ifndef GLMatrix_hpp
#define GLMatrix_hpp

#include <string>
#include <stdio.h>
#include <OpenGLES/ES2/gl.h>
#include "GDirector.hpp"
#include "GTypes.hpp"

class GLMatrix
{
    
public:
    GLfloat* Matrix();
    
    void gMatrix(kmMat4* aMat);
    void PopulateOrtho(GLfloat aLeft,
                       GLfloat aRight,
                       GLfloat aBottom,
                       GLfloat aTop,
                       GLfloat aNear,
                       GLfloat aFar);

    void PopulateFromTranslation(const kmVec3& translation);
    void PopulateIdentity();
    void AddTranslation(const kmVec3& translation);


    kmVec3 GetTranslation();
    
private:
    bool mInitialized = false;
    kmMat4 glMatrix;
};


#endif /* GLMatrix_hpp */

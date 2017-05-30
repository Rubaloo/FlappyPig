//
//  m1.cpp
//  Flapi Pig
//
//  Created by Ruben on 17/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//
#include "GLMatrix.hpp"

static const GLfloat identityContents[] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f };

GLfloat* GLMatrix::matrix() {
    return glMatrix.mat;
};

void GLMatrix::gMatrix(kmMat4* gMatrix) {
    float *m1 = glMatrix.mat;
    gMatrix->mat[0]  = m1[0];
    gMatrix->mat[1]  = m1[1];
    gMatrix->mat[2]  = m1[2];
    gMatrix->mat[3] = m1[3];
    
    gMatrix->mat[4]  = m1[4];
    gMatrix->mat[5]  = m1[5];
    gMatrix->mat[6]  = m1[6];
    gMatrix->mat[7] = m1[7];
    
    gMatrix->mat[8]  = m1[8];
    gMatrix->mat[9]  = m1[9];
    gMatrix->mat[10]  = m1[10];
    gMatrix->mat[11] = m1[11];
    
    gMatrix->mat[12] = (m1[12]*ASPECT_RATIO)/SCREEN_WIDTH;
    gMatrix->mat[13] = m1[13]/SCREEN_HEIGHT;
    gMatrix->mat[14] = m1[14];
    gMatrix->mat[15] = m1[15];
};

void GLMatrix::populateIdentity() {
    initialized = true;
    float *m1 = glMatrix.mat;
    m1[0]  = identityContents[0];
    m1[1]  = identityContents[1];
    m1[2]  = identityContents[2];
    m1[3] = identityContents[3];

    m1[4]  = identityContents[4];
    m1[5]  = identityContents[5];
    m1[6]  = identityContents[6];
    m1[7] = identityContents[7];

    m1[8]  = identityContents[8];
    m1[9]  = identityContents[9];
    m1[10]  = identityContents[10];
    m1[11] = identityContents[11];

    m1[12]  = identityContents[12];
    m1[13]  = identityContents[13];
    m1[14] = identityContents[14];
    m1[15] = identityContents[15];
}

void GLMatrix::populateOrtho(GLfloat left,
                   GLfloat right,
                   GLfloat bottom,
                   GLfloat top,
                   GLfloat near,
                   GLfloat far) {

    float *m1 = glMatrix.mat;
    m1[0]  = 2.0 / (right - left);
    m1[1]  = 0.0;
    m1[2]  = 0.0;
    m1[3] = 0.0;
    
    m1[4]  = 0.0;
    m1[5]  = 2.0 / (top - bottom);
    m1[6]  = 0.0;
    m1[7] = 0.0;
    
    m1[8]  = 0.0;
    m1[9]  = 0.0;
    m1[10]  = -2.0 / (far - near);
    m1[11] = 0.0;
    
    m1[12]  = -(right + left) / (right - left);
    m1[13]  = -(top + bottom) / (top - bottom);
    m1[14] = -(far + near) / (far - near);
    m1[15] = 1.0;
}

void GLMatrix::addTranslation(kmVec3 translation)
{
    float *m1 = glMatrix.mat;
    m1[12] = m1[12] + translation.x;
    m1[13] = m1[13] + translation.y;
    m1[14] = m1[14] + translation.z;
}

kmVec3 GLMatrix::getTranslation()
{
    float *m1 = glMatrix.mat;
    return kmVec3Make(m1[12], m1[13], m1[14]);
}

void GLMatrix::populateFromTranslation (kmVec3 tVector) {
    populateIdentity();
    
    float *m1 = glMatrix.mat;
    m1[12] = tVector.x;
    m1[13] = tVector.y;
    m1[14] = tVector.z;
}

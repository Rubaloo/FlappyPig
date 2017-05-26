//
//  GTypes.hpp
//  Flapi Pig
//
//  Created by Ruben on 18/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//


#ifndef GTypes_hpp
#define GTypes_hpp


#define KM_FALSE 0
#define KM_TRUE 1
#define SCREEN_WIDTH GDirector::getInstance()->getWinSizeInPixels().w
#define SCREEN_HEIGHT GDirector::getInstance()->getWinSizeInPixels().h
#define ASPECT_RATIO SCREEN_WIDTH/SCREEN_HEIGHT
#define kmScalar GLfloat
#include <OpenGLES/ES2/gl.h>


typedef struct glVertex {
    kmScalar position[3];
    kmScalar color[4];
} glVertex;

/** A homogeneous four-dimensional vector. */
typedef struct kmVec4 {
    kmScalar x;
    kmScalar y;
    kmScalar z;
    kmScalar w;
} kmVec4;

typedef struct kmSize{
    kmScalar w;
    kmScalar h;
} kmSize;

/** A three-dimensional vector. */
typedef struct kmVec3 {
    kmScalar x;
    kmScalar y;
    kmScalar z;
} kmVec3;

typedef struct kmVertex{
    kmVec3 position;
    kmVec4 color;
} kmVertex;

typedef struct kmRect {
    kmVec3 br;
    kmVec3 bl;
    kmVec3 tr;
    kmVec3 tl;
} kmRect;

/** A homogeneous four-dimensional vector. */
/** A rotational quaternion */
typedef struct kmQuaternion {
    kmScalar x;
    kmScalar y;
    kmScalar z;
    kmScalar w;
} kmQuaternion;

/** A standard 4x4 matrix */
typedef struct {
    kmScalar mat[16];
} kmMat4;


kmVec3 kmVec3Add(kmVec3 v, kmVec3 k);
kmVec3 kmVec3Sub(kmVec3 v, kmVec3 k);

kmVec4 kmVec4Make(kmScalar x, kmScalar y, kmScalar z, kmScalar w);
kmVertex kmVertexMake(kmVec3 position, kmVec4 color);

/** Returns a kmVec3 structure constructed from the vector components. */
kmVec3 kmVec3Make(kmScalar x, kmScalar y, kmScalar z);

/** Returns the length of the vector. */
kmScalar kmVec3Length(const kmVec3* pIn);

/** Normalizes the vector to unit length, stores the result in pOut and returns the result. */
kmVec3* kmVec3Normalize(kmVec3* pOut, const kmVec3* pIn);

/** Multiplies pM1 with pM2, stores the result in pOut, returns pOut. */
kmMat4* kmMat4Multiply(kmMat4* pOut, const kmMat4* pM1, const kmMat4* pM2);

/**
 * Builds a rotation matrix that rotates around all three axes, y (yaw), x (pitch) and z (roll),
 * in that order, stores the result in pOut and returns the result.
 * This algorithm matches up along the positive Y axis, which is the OpenGL ES default.
 */
kmMat4* kmMat4RotationYXZ(kmMat4* pOut, const kmScalar xRadians, const kmScalar yRadians, const kmScalar zRadians);

/**
 * Builds a rotation matrix that rotates around all three axes z (roll), y (yaw), and x (pitch),
 * in that order, stores the result in pOut and returns the result
 * This algorithm matches up along the positive Z axis, which is used by some commercial 3D worlds.
 */
kmMat4* kmMat4RotationZYX(kmMat4* pOut, const kmScalar xRadians, const kmScalar yRadians, const kmScalar zRadians);

/** Builds a rotation matrix around the X-axis, stores the result in pOut and returns the result */
kmMat4* kmMat4RotationX(kmMat4* pOut, const float radians);

/** Builds a rotation matrix around the Y-axis, stores the result in pOut and returns the result */
kmMat4* kmMat4RotationY(kmMat4* pOut, const float radians);

/** Builds a rotation matrix around the Z-axis, stores the result in pOut and returns the result */
kmMat4* kmMat4RotationZ(kmMat4* pOut, const float radians);

/**
 * Build a rotation matrix from an axis and an angle,
 * stores the result in pOut and returns the result.
 */
kmMat4* kmMat4RotationAxisAngle(kmMat4* pOut, const kmVec3* axis, kmScalar radians);

/**
 * Builds a rotation matrix from a quaternion to a rotation matrix,
 * stores the result in pOut and returns the result.
 */
kmMat4* kmMat4RotationQuaternion(kmMat4* pOut, const kmQuaternion* pQ);

/** Extracts a quaternion from a rotation matrix, stores the result in quat and returns the result */
kmQuaternion* kmQuaternionRotationMatrix(kmQuaternion* quat, const kmMat4* pIn);

/**
 * Builds a transformation matrix that translates, rotates and scales according to the specified vectors,
 * stores the result in pOut and returns the result.
 */
kmMat4* kmMat4Transformation(kmMat4* pOut, const kmVec3 translation, const kmVec3 rotation, const kmVec3 scale);

/** Gauss-Jordan matrix inversion function */
int kmGaussJordan(kmMat4 *a, kmMat4 *b);

/** Get the value from the matrix at the specfied row and column. */
float kmMatGet(const kmMat4* pIn, int row, int col);

/** Set the value into the matrix at the specfied row and column. */
void kmMatSet(kmMat4 * pIn, int row, int col, float value);

/** Swap the elements in the matrix at the specfied row and column coordinates. */
void kmMatSwap(kmMat4 * pIn, int r1, int c1, int r2, int c2);

kmSize kmSizeMake(kmScalar width, kmScalar height);
#endif /* GTypes_hpp */

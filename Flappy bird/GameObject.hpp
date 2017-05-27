//
//  GameObject.hpp
//  Flapi Pig
//
//  Created by Ruben on 13/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include <iostream>
#include <stdio.h>
#include <vector>
#include <OpenGLES/ES2/gl.h>
#include "GLMatrix.hpp"
#include "GDirector.hpp"
#include "GTypes.hpp"
#include "GLVertex.hpp"
#include "Box.hpp"
#include "VertexArray.hpp"
#include "GLMatrix.hpp"

using namespace std;

class GameObject {

protected:
    
    GLMatrix modelView;
    Box body;
    vector<glVertex> vertexs;
    VertexArray* modelMesh;

public:
    GameObject();
    GameObject(Box b);
    bool outsideLeftLimits();
    void moveTo(kmVec3 translation);
    virtual void update(float dt){};
    virtual void render(){};
    Box* getBox();
};
#endif /* GameObject_hpp */

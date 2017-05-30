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
#include "GBox.hpp"
#include "GVertexArray.hpp"
#include "GLMatrix.hpp"

using namespace std;

class GameObject {

protected:
    
    GLMatrix modelView;
    GBox body;
    vector<glVertex> vertexs;
    GVertexArray* modelMesh;

public:
    GameObject();
    GameObject(GBox b);
    
    bool reachTop();
    bool reachFloor();
    bool outsideLeftLimits();
    bool intersect(GBox* GBox);
    bool intersect(GameObject* object);
    void moveTo(kmVec3 translation);
    void resetModelView();
    virtual void update(float dt){};
    virtual void render(){};
    GBox* getBox();
};
#endif /* GameObject_hpp */

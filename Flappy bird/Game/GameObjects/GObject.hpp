//
//  GObject.hpp
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

class GObject {

protected:
    GBox body;
    GVertexArray* modelMesh;
    GLMatrix modelView;

public:
    GObject();
    GObject(GBox b);
    
    GBox* getBox();
    
    void moveTo(kmVec3 translation);
    void resetModelView();
    
    bool intersect(GObject* object);
    bool reachTop();
    bool reachFloor();
    bool outsideLeftLimits();
    
    virtual void update(float dt){};
    virtual void render(){};
};
#endif /* GameObject_hpp */

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

using namespace std;

class GameObject {

protected:
    Box body;
    vector<glVertex> vertexs;
    vector<GLubyte> indexs;

public:
    GameObject();
    GameObject(Box b);
    void update(float dt){};
    void addVertexs(vector<glVertex>* vertexs);
    void addIndexs(vector<GLubyte>* geometry);
};
#endif /* GameObject_hpp */

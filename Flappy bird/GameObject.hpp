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

using namespace std;

class GameObject {
private:
    //Body body;
    //fvec direction; to Body
    //fvec velocity; to Body
    //bool isVisible; to Body
    
    //fvec moveTo(fvec direction); to Body
    //bool intersect(GameObject gameObject); to Body
protected:
    vector<glVertex> vertexs;
    vector<GLubyte> indexs;

public:
    void update(float dt){};
    void addVertexs(vector<glVertex>* vertexs);
    void addIndexs(vector<GLubyte>* geometry);
};
#endif /* GameObject_hpp */

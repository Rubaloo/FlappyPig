//
//  GameObject.cpp
//  Flapi Pig
//
//  Created by Ruben on 13/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#include "GameObject.hpp"

GameObject::GameObject(){}
GameObject::GameObject(Box b)
{
    body = b;
}

void GameObject::addVertexs(vector<glVertex>* geometry)
{
    vertexs.clear();
    
    kmVec4 red = kmVec4Make(1.0, 0.0, 0.0, 1.0);
    kmVec4 blue = kmVec4Make(0.0, 0.0, 1.0, 1.0);
    kmVec4 green = kmVec4Make(0.0, 1.0, 0.0, 1.0);
    
    vector<kmVec3> boxV = body.getVertexs();
    
    GLVertex gv1(boxV[0], red);
    GLVertex gv2(boxV[1],blue);
    GLVertex gv3(boxV[2], green);
    GLVertex gv4(boxV[3],red);
        
    vertexs.push_back(gv1.glVertex());
    vertexs.push_back(gv2.glVertex());
    vertexs.push_back(gv3.glVertex());
    vertexs.push_back(gv4.glVertex());
        
    geometry->insert(geometry->end(), vertexs.begin(), vertexs.end());

}
void GameObject::addIndexs(vector<GLubyte>* index)
{
    indexs.clear();
    indexs.push_back(0);
    indexs.push_back(1);
    indexs.push_back(2);
    indexs.push_back(3);
    index->insert(index->end(), indexs.begin(), indexs.end());
}


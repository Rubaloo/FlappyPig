//
//  GameObject.cpp
//  Flapi Pig
//
//  Created by Ruben on 13/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#include "GameObject.hpp"

void GameObject::addVertexs(vector<glVertex>* geometry)
{
    geometry->insert(geometry->end(), vertexs.begin(), vertexs.end());

}
void GameObject::addIndexs(vector<GLubyte>* index)
{
    index->insert(index->end(), indexs.begin(), indexs.end());
}


//
//  Box.cpp
//  Flappy bird
//
//  Created by Ruben on 21/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#include "Box.hpp"

Box::Box(){};
Box::Box(kmVec3 c, kmSize s)
{
    center = c;
    size = s;
}

//triangle strip box representation
vector<kmVec3> Box::getVertexs()
{
    vector<kmVec3> vertexs;
    GLfloat hWidth = size.w/2.0;
    GLfloat hHeight = size.h/2.0;
    
    kmVec3 bl = kmVec3Make(center.x - hWidth , center.y - hHeight, 0.0);
    kmVec3 br = kmVec3Make(center.x + hWidth , center.y - hHeight, 0.0);
    kmVec3 tl = kmVec3Make(center.x - hWidth , center.y + hHeight, 0.0);
    kmVec3 tr = kmVec3Make(center.x + hWidth , center.y + hHeight, 0.0);
    
    vertexs.push_back(bl); vertexs.push_back(br); vertexs.push_back(tl); vertexs.push_back(tr);
    return vertexs;
}


bool Box::moveTo(kmVec3 direction) {
    return true;
};

bool Box::intersect(Box* gameObject) {
    return true;
};

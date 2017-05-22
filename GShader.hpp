//
//  GShader.hpp
//  Flappy bird
//
//  Created by Ruben on 22/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#ifndef GShader_hpp
#define GShader_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include "GTypes.hpp"
#include "ShaderUtils.hpp"

#include <OpenGLES/ES2/gl.h>

using namespace std;

class GShader {
public:
    GShader(string vertex, string fragment);

//    static GShader* BIRD;
//    static void loadAll();
    
    GLuint getUniform(string name);
    
    void setUniform3f(string name, kmVec3 vector);
    void setUniform4f(string name, kmMat4 matrix);
    void enable();
    void disable();
    
private:
    bool enabled;
    GLuint ID;
    
};
#endif /* GShader_hpp */
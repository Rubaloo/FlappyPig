//
//  GShaderUtils.hpp
//  Flappy bird
//
//  Created by Ruben on 22/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#ifndef GShaderUtils_hpp
#define GShaderUtils_hpp

#include <stdio.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <OpenGLES/ES2/gl.h>

using namespace std;

class GShaderUtils
{
private:
    static bool instanceFlag;
    static GShaderUtils *single;
    
    GShaderUtils(){}
    
    GLuint create();
    GLuint compileShader(string shaderName, GLenum shaderType);
    
    string readFile(char* fileName);
public:
    static GShaderUtils* getInstance();
    ~GShaderUtils()
    {
        instanceFlag = false;
    }
    GLuint load(string vertexName, string fragmentName);
};
#endif /* GShaderUtils_hpp */

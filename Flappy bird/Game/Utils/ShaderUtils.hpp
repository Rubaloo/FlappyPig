//
//  ShaderUtils.hpp
//  Flappy bird
//
//  Created by Ruben on 22/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#ifndef ShaderUtils_hpp
#define ShaderUtils_hpp

#include <stdio.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <OpenGLES/ES2/gl.h>

using namespace std;

class ShaderUtils
{
private:
    static bool instanceFlag;
    static ShaderUtils *single;
    ShaderUtils(){}
    GLuint compileShader(string shaderName, GLenum shaderType);
    string readFile(char* fileName);
    GLuint create();
public:
    static ShaderUtils* getInstance();
    ~ShaderUtils()
    {
        instanceFlag = false;
    }
    GLuint load(string vertexName, string fragmentName);
};
#endif /* ShaderUtils_hpp */

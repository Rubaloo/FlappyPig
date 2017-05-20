//
//  Shader.hpp
//  Flapi Pig
//
//  Created by Ruben on 14/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <OpenGLES/ES2/gl.h>

using namespace std;

class Shader
{
private:
    string vertexFileName;
    string fragmentFileName;
    GLuint program;
    
    GLuint compileShader(string shaderName, GLenum shaderType);
    string readFile(char* fileName); //Improve 
public:
    Shader(string vertexShader, string fragmentShader);
    GLuint getProgram();
    bool compileAndLink();
    
};
#endif /* Shader_hpp */

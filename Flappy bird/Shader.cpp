//
//  Shader.cpp
//  Flapi Pig
//
//  Created by Ruben on 14/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#include "IO-C-Interface.h"
#include "Shader.hpp"
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

Shader::Shader(string vertexName, string fragmentName)
{
    vertexFileName = vertexName;
    fragmentFileName = fragmentName;
}

bool Shader::compileAndLink()
{
    GLuint vertexShader = compileShader(vertexFileName, GL_VERTEX_SHADER);
    GLuint fragmentShader = compileShader(fragmentFileName, GL_FRAGMENT_SHADER);
    
    // 2
    GLuint programHandle = glCreateProgram();
    glAttachShader(programHandle, vertexShader);
    glAttachShader(programHandle, fragmentShader);
    glLinkProgram(programHandle);
    
    // 3
    GLint linkSuccess;
    glGetProgramiv(programHandle, GL_LINK_STATUS, &linkSuccess);
    if (linkSuccess == GL_FALSE) {
        GLchar messages[256];
        glGetProgramInfoLog(programHandle, sizeof(messages), 0, &messages[0]);
        printf("%s", messages);
        return false;
    }
    
    program = programHandle;
    return true;
}

GLuint Shader::compileShader(string shaderFileName, GLenum shaderType)
{
    string shaderString = readFile(&shaderFileName[0]);
    // 2
    GLuint shaderHandle = glCreateShader(shaderType);
    
    // 3
    const char * shaderStringUTF8 = &shaderString[0];
    int shaderStringLength = shaderString.length();
    glShaderSource(shaderHandle, 1, &shaderStringUTF8, &shaderStringLength);
    
    // 4
    glCompileShader(shaderHandle);
    
    // 5
    GLint compileSuccess;
    glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compileSuccess);
    if (compileSuccess == GL_FALSE) {
        GLchar messages[256];
        glGetShaderInfoLog(shaderHandle, sizeof(messages), 0, &messages[0]);
        char * messageString = messages;
        printf("%s", messageString);
        return -1;
    }
    return shaderHandle;
}

GLuint Shader::getProgram() {
    return program;
}

string Shader::readFile(char* fileName)
{
    return string(myreadFile(fileName));
}

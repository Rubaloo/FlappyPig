//
//  GShaderUtils.cpp
//  Flappy bird
//
//  Created by Ruben on 22/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#include "GShaderUtils.hpp"

#include "IO-C-Interface.h"
#include "GShaderUtils.hpp"
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

#include "GShaderUtils.hpp"


bool GShaderUtils::instanceFlag = false;
GShaderUtils* GShaderUtils::single = NULL;
GShaderUtils* GShaderUtils::getInstance()
{
    if(!instanceFlag)
    {
        single = new GShaderUtils();
        instanceFlag = true;
        return single;
    }
    else
    {
        return single;
    }
}


GLuint GShaderUtils::load(string vertexName, string fragmentName)
{
    GLuint vertexShader = compileShader(vertexName, GL_VERTEX_SHADER);
    GLuint fragmentShader = compileShader(fragmentName, GL_FRAGMENT_SHADER);
    
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
    
    return programHandle;
}

GLuint GShaderUtils::compileShader(string shaderFileName, GLenum shaderType)
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

string GShaderUtils::readFile(char* fileName)
{
    return string(iOSreadFile(fileName));
}

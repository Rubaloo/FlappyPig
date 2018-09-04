#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include "GShaderUtils.hpp"
#include "IO-C-Interface.h"

using namespace std;

bool GShaderUtils::sInstanceFlag = false;
GShaderUtils* GShaderUtils::sSingle = NULL;

GShaderUtils* GShaderUtils::GetInstance()
{
    if(!sInstanceFlag)
    {
        sSingle = new GShaderUtils();
        sInstanceFlag = true;
        return sSingle;
    }
    else
    {
        return sSingle;
    }
}


GLuint GShaderUtils::Load(const string& aVertexName, const string& aFragmentName)
{
    GLuint vertexShader = CompileShader(aVertexName, GL_VERTEX_SHADER);
    GLuint fragmentShader = CompileShader(aFragmentName, GL_FRAGMENT_SHADER);
    
    GLuint programHandle = glCreateProgram();
    glAttachShader(programHandle, vertexShader);
    glAttachShader(programHandle, fragmentShader);
    glLinkProgram(programHandle);
    
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

GLuint GShaderUtils::CompileShader(const string& aShaderFileName, GLenum aShaderType)
{
    const char * shaderStringUTF8 = ReadFile(&aShaderFileName[0]);
    GLuint shaderHandle = glCreateShader(aShaderType);
    GLint shaderLength = static_cast<GLint>(strlen(shaderStringUTF8));
    glShaderSource(shaderHandle, 1, &shaderStringUTF8, &shaderLength);
    
    glCompileShader(shaderHandle);
    
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

const char* GShaderUtils::ReadFile(const char* fileName)
{
    return iOSReadFile(fileName);
}

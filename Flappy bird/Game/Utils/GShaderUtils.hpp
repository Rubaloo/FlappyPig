#ifndef GShaderUtils_hpp
#define GShaderUtils_hpp

#include <stdio.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <OpenGLES/ES2/gl.h>


class GShaderUtils
{
private:
    static bool sInstanceFlag;
    static GShaderUtils* sSingle;
    
    GShaderUtils(){}
    
    GLuint Create();
    GLuint CompileShader(const std::string& aShaderName, GLenum aShaderType);
    
    const char* ReadFile(const char* fileName);
public:
    static GShaderUtils* GetInstance();
    ~GShaderUtils()
    {
        sInstanceFlag = false;
    }
    GLuint Load(const std::string& aVertexName, const std::string& aFragmentName);
};
#endif /* GShaderUtils_hpp */

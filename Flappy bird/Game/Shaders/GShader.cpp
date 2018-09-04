#include "GShader.hpp"

#define BIRD_VERTEX_SHADER "BirdVertex"
#define BIRD_FRAGMENT_SHADER "BirdFragment"
#define PIPE_VERTEX_SHADER "PipeVertex"
#define PIPE_FRAGMENT_SHADER "PipeFragment"


GShader* GShader::BIRD;
GShader* GShader::PIPE;

GShader::GShader(const char* aVertexName, const char* aFragmentName) : mEnabled(false),
    mID(GShaderUtils::GetInstance()->Load(aVertexName, aFragmentName))
{
}

GLuint GShader::GetID() {
    return mID;
};

void GShader::LoadAll() {
    BIRD = new GShader(BIRD_VERTEX_SHADER, BIRD_FRAGMENT_SHADER);
    PIPE = new GShader(PIPE_VERTEX_SHADER, PIPE_FRAGMENT_SHADER);
}

GLuint GShader::GetUniform(const char* aName) {
    GLuint result = glGetUniformLocation(mID, aName);
    if(result == -1) {
        printf("Cannot find uniform variable: %s", aName);
    }
    return result;
}

GLuint GShader::GetAttribute(const char* aName) {
    GLuint result = glGetAttribLocation(mID, aName);
    if(result == -1) {
        printf("Cannot find attribute variable: %s", aName);
    }
    return result;
}

void GShader::EnableVertexAttribute(const char* aName)
{
    glEnableVertexAttribArray(GetAttribute(aName));
}

void GShader::SetUniform1f(const char* aName, GLfloat f) {
    if (!mEnabled) Enable();
    glUniform1f(GetUniform(aName), f);
}

void GShader::SetUniform2f(const char* aName, GLfloat x, GLfloat y) {
    if (!mEnabled) Enable();
    glUniform2f(GetUniform(aName), x, y);
}

void GShader::SetUniform3f(const char* aName, kmVec3 vector) {
    if (!mEnabled) Enable();
    glUniform3f(GetUniform(aName), vector.x, vector.y, vector.z);
}

void GShader::SetUniform4f(const char* aName, GLfloat* matrix) {
    if (!mEnabled) Enable();
    glUniformMatrix4fv(GetUniform(aName), 1, GL_FALSE, matrix);
}

void GShader::Enable() {
    glUseProgram(mID);
    mEnabled = true;
};

void GShader::Disable() {
    glUseProgram(0);
    mEnabled = false;
}

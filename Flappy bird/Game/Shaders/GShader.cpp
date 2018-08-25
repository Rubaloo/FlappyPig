#include "GShader.hpp"

#define BIRD_VERTEX_SHADER "BirdVertex"
#define BIRD_FRAGMENT_SHADER "BirdFragment"
#define PIPE_VERTEX_SHADER "PipeVertex"
#define PIPE_FRAGMENT_SHADER "PipeFragment"


GShader* GShader::BIRD;
GShader* GShader::PIPE;

GShader::GShader(string vertexName, string fragmentName) {
    enabled = false;
    ID = GShaderUtils::getInstance()->load(vertexName, fragmentName);
}

GShader::~GShader(){}

GLuint GShader::getID() {
    return ID;
};

void GShader::loadAll() {
    BIRD = new GShader(BIRD_VERTEX_SHADER, BIRD_FRAGMENT_SHADER);
    PIPE = new GShader(PIPE_VERTEX_SHADER, PIPE_FRAGMENT_SHADER);
}

GLuint GShader::getUniform(string name) {
    GLuint result = glGetUniformLocation(ID, name.c_str());
    if(result == -1) {
        printf("Cannot find uniform variable: %s", name.c_str());
    }
    return result;
}

GLuint GShader::getAttribute(string name) {
    GLuint result = glGetAttribLocation(ID, name.c_str());
    if(result == -1) {
        printf("Cannot find attribute variable: %s", name.c_str());
    }
    return result;
}

void GShader::enableVertexAttribute(string name)
{
    glEnableVertexAttribArray(getAttribute(name));
}

void GShader::setUniform1f(string name, GLfloat f) {
    if (!enabled) enable();
    glUniform1f(getUniform(name), f);
}

void GShader::setUniform2f(string name, GLfloat x, GLfloat y) {
    if (!enabled) enable();
    glUniform2f(getUniform(name), x, y);
}

void GShader::setUniform3f(string name, kmVec3 vector) {
    if (!enabled) enable();
    glUniform3f(getUniform(name), vector.x, vector.y, vector.z);
}

void GShader::setUniform4f(string name, GLfloat* matrix) {
    if (!enabled) enable();
    glUniformMatrix4fv(getUniform(name), 1, GL_FALSE, matrix);
}

void GShader::enable() {
    glUseProgram(ID);
    enabled = true;
};

void GShader::disable() {
    glUseProgram(0);
    enabled = false;
}

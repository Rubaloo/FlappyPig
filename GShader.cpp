//
//  GShader.cpp
//  Flappy bird
//
//  Created by Ruben on 22/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#include "GShader.hpp"

GShader* GShader::BIRD;

GShader::GShader(string vertexName, string fragmentName) {
    enabled = false;
    ID = ShaderUtils::getInstance()->load(vertexName, fragmentName);
}

GLuint GShader::getID() {
    return ID;
};

void GShader::loadAll() {
    BIRD = new GShader("SimpleVertex", "SimpleFragment");
}

GLuint GShader::getUniform(string name) {
    GLuint result = glGetUniformLocation(ID, name.c_str());
    if(result == -1) {
        printf("Cannot find uniform variable: %s", name.c_str());
    }
    else {
        // save to cache
    }
    return result;
}

GLuint GShader::getAttribute(string name) {
    GLuint result = glGetAttribLocation(ID, name.c_str());
    if(result == -1) {
        printf("Cannot find attribute variable: %s", name.c_str());
    }
    else {
        // save to cache
    }
    return result;
}

void GShader::enableVertexAttribute(string name)
{
    glEnableVertexAttribArray(getAttribute(name));
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

#pragma once

#define PROGRAM_VERTEX_ATTRIBUTE 0
#define PROGRAM_COLOR_ATTRIBUTE 1

#include <memory>
#include <QGLShaderProgram>
#include <QGLShader>

using namespace std;

class GLShader
{
public:
    GLShader(const char* vertexShaderFile, const char* fragmentShaderFile, shared_ptr<QGLShaderProgram> &program);
    void activateShader();
    void activateShaderTexture();
};

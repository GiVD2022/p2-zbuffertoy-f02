#pragma once

#include <memory>
#include <stdlib.h>
#include <QGLShaderProgram>

using namespace std;

class GPUConnectable
{
public:
    GPUConnectable() {};
    ~GPUConnectable() {};

    virtual void toGPU(shared_ptr<QGLShaderProgram> p) = 0;
    virtual void draw() {};

protected:
    shared_ptr<QGLShaderProgram> program;
};

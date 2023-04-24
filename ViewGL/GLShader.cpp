#include "GLShader.hh"

GLShader::GLShader(const char* vShaderFile, const char* fShaderFile, shared_ptr<QGLShaderProgram> &program){
    QGLShader *vshader = new QGLShader(QGLShader::Vertex);
    QGLShader *fshader = new QGLShader(QGLShader::Fragment);

    vshader->compileSourceFile(vShaderFile);
    fshader->compileSourceFile(fShaderFile);

    program = std::make_shared<QGLShaderProgram>();
    program->addShader(vshader);
    program->addShader(fshader);
}

//Metode per activar un shader
void GLShader::activateShader(){


;}

//Metode per activar shaders de textures
void GLShader::activateShaderTexture(){
    //TO DO: Pràctica 2:  implementar a la fase 1

}

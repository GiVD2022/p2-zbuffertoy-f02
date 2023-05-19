#include "ScaleTG.hh"


ScaleTG::ScaleTG(vec3 escala): escala(escala)
{
    matTG = Scale(escala);
}

ScaleTG::~ScaleTG() {}

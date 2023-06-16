#include "ScaleTG.hh"

ScaleTG::ScaleTG(vec3 scale) : scaling(scale)
{
    matTG = Scale(scaling);
}

ScaleTG::~ScaleTG()
{

}

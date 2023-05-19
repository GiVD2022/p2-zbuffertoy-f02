#ifndef SCALETG_HH
#define SCALETG_HH

#include "TG.hh"

class ScaleTG: public TG
{
public:
    vec3 escala;
    ScaleTG(vec3 escala);
    virtual ~ScaleTG();
};

#endif // SCALETG_HH

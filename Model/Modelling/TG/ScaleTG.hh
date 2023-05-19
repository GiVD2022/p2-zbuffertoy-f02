#ifndef SCALETG_H
#define SCALETG_H

#include "TG.hh"

class ScaleTG : public TG
{
public:
    vec3 scaling;

    ScaleTG(vec3 scale);
    virtual ~ScaleTG();
};

#endif // SCALETG_H

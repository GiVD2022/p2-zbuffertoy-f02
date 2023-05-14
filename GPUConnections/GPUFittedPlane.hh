#pragma once

#include "GPUConnectable.hh"
#include "Model/Modelling/Objects/FittedPlane.hh"


class GPUFittedPlane: public FittedPlane, public GPUConnectable
{
public:
    GPUFittedPlane();
};


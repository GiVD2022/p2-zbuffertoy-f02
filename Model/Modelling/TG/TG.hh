#pragma once

#include "library/Common.h"

class TG
{
public:
    mat4 matTG;
    TG();
    ~TG();
    virtual mat4 getTG();
};



#include "TG.hh"

TG::TG()
{
 matTG = mat4(1.0f);
}

TG::~TG()
{

}

mat4 TG::getTG() {
    return matTG;
}

#include "TranslateTG.hh"

TranslateTG::TranslateTG(vec3 trasl): traslation(trasl)
{
    matTG = Translate(traslation);
}

TranslateTG::~TranslateTG()
{

}

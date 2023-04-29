#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include "Light.hh"

class SpotLight: public Light
{
public:
    SpotLight();
    /*
     * Constructor de la classe SpotLight.
     * param posicio: posició de la llum.
     * param Ia: component ambient de la llum.
     * param Id: component difosa de la llum.
     * param Is: component especular de la llum.
     * param spotDirection: direcció de la llum
     * param spotCosineCutoff: angle de la llum
     * param spotExponent: no negatiu que determina com la intensitat disminueix
     * */
    SpotLight(vec3 posicio, vec3 Ia, vec3 Id, vec3 Is, vec3 spotDirection, float spotCosineCutoff, float spotExponent);
    virtual ~SpotLight() {}
    vec3 getPos();
    virtual vec3 vectorL(vec3 point) override;
    virtual float attenuation(vec3 point) override;
    virtual float distanceToLight(vec3 point) override;

    virtual void read (const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;

    vec3 getSpotDirection();
    float getSpotCosineCutoff();
    float getSpotExponent();
private:
    vec3 position;
    vec3 spotDirection;
    float spotCosineCutoff;
    float spotExponent;
};
#endif // SPOTLIGHT_H

#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include "Light.hh"

class DirectionalLight: public Light {
public:
    DirectionalLight() {};
    /*
     * Constructor de la classe PointLight.
     * param Ia: component ambient de la llum.
     * param Id: component difosa de la llum.
     * param Is: component especular de la llum.
     * param direction: direcció de la llum
     * param intensity: intensitat de la llum
     * */
    DirectionalLight(vec3 direction, vec3 Ia, vec3 Id, vec3 Is, float intensity);
    virtual ~DirectionalLight() {}
    vec3 getDirection();
    float getIntensity();
    virtual vec3 vectorL(vec3 point) override;
    virtual float attenuation(vec3 point) override;
    virtual float distanceToLight(vec3 point) override;

    virtual void read (const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;
private:
    float intensity;
    vec3 direction;
};

#endif // DIRECTIONALLIGHT_H

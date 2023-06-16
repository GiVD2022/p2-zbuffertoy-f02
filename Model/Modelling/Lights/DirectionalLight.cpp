#include "DirectionalLight.hh"

DirectionalLight::DirectionalLight(vec3 direction, vec3 Ia, vec3 Id, vec3 Is, float intensity): Light(Ia, Id, Is)
{
    this->direction = direction;
    this->intensity = intensity;
}

vec3 DirectionalLight::getDirection()
{
    return this->direction;
}

void DirectionalLight::setDirection(vec3 dir)
{
    this->direction = dir;
}

float DirectionalLight::getIntensity()
{
    return this->intensity;
}

void DirectionalLight::setIntensity(float intensity)
{
    this->intensity = intensity;
}

vec3 DirectionalLight::vectorL(vec3 point) {
    return - normalize(this->direction);
}

float DirectionalLight::attenuation(vec3 point) {
    return 1.0f;
}

float DirectionalLight::distanceToLight(vec3 point) {
    return 10000000; //està a infty
}

void DirectionalLight::read (const QJsonObject &json)
{
    Light::read(json);

    if (json.contains("direction") && json["direction"].isArray()) {
        QJsonArray auxVec = json["direction"].toArray();
        direction[0] = auxVec[0].toDouble();
        direction[1] = auxVec[1].toDouble();
        direction[2] = auxVec[2].toDouble();
    }
    if (json.contains("intensity") && json["intensity"].isDouble())
        intensity = json["intensity"].toDouble();
}

//! [1]
void DirectionalLight::write(QJsonObject &json) const
{
    Light::write(json);
    QJsonArray auxArray;
    auxArray.append(direction[0]);auxArray.append(direction[1]);auxArray.append(direction[2]);
    json["direction"] = auxArray;

    json["intensity"] = intensity;

}
//! [1]

void DirectionalLight::print(int indentation) const
{
    const QString indent(indentation * 2, ' ');

    QTextStream(stdout) << "Directional Light" << "\n";
    QTextStream(stdout) << indent + 2 << "direction:\t" << direction[0] << ", "<< direction[1] << ", "<< direction[2] << "\n";
    QTextStream(stdout) << indent + 2 << "intensity:\t" << intensity << "\n";


}

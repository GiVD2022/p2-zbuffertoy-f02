#include "SpotLight.hh"

SpotLight::SpotLight(){}

SpotLight::SpotLight(vec3 posicio, vec3 Ia, vec3 Id, vec3 Is, vec3 spotDirection, float spotCosineCutoff, float spotExponent): Light(Ia, Id, Is) {
    this->position = posicio;
    this->spotDirection = spotDirection;
    this->spotCosineCutoff = spotCosineCutoff;
    this->spotExponent = spotExponent;
}

vec3 SpotLight::getPosition() {
    return this->position;
}

void SpotLight::setPosition(vec3 v) {
    this->position = v;
}

vec3 SpotLight::getSpotDirection(){
    return this->spotDirection;
}

void SpotLight::setSpotDirection(vec3 spotdir) {
    this->spotDirection = spotdir;
}

float SpotLight::getSpotCosineCutoff(){
    return this->spotCosineCutoff;
}

void SpotLight::setSpotCosineCutoff(float spotcoscutoff) {
    this->spotCosineCutoff = spotcoscutoff;
}

float SpotLight::getSpotExponent(){
    return this->spotExponent;
}

void SpotLight::setSpotExponent(float spotexp) {
    this->spotExponent = spotexp;
}

vec3 SpotLight::vectorL(vec3 point) {
    return normalize(position - point);
}

float SpotLight::attenuation(vec3 point) {
    // https://math.hws.edu/graphicsbook/c7/s2.html#webgl3d.2.6
    float spotFactor = 1.0;  // multiplier to account for spotlight

    if (spotCosineCutoff > 0.0) { // the light is a spotlight
        vec3 D = -normalize(spotDirection);
        vec3 L = -normalize(position - point);
        float spotCosine = dot(D,L);
        if (spotCosine >= spotCosineCutoff) {
            spotFactor = pow(spotCosine,spotExponent);
        }
        else { // The point is outside the cone of light from the spotlight.
            spotFactor = 0.0; // The light will add no color to the point.
        }
    }
    return spotFactor;
}

float SpotLight::distanceToLight(vec3 point) {
    return distance(point, position);
}

void SpotLight::read (const QJsonObject &json)
{
    Light::read(json);

    if (json.contains("position") && json["position"].isArray()) {
        QJsonArray auxVec = json["position"].toArray();
        position[0] = auxVec[0].toDouble();
        position[1] = auxVec[1].toDouble();
        position[2] = auxVec[2].toDouble();
    }
    if (json.contains("direction") && json["direction"].isArray()) {
        QJsonArray auxVec = json["position"].toArray();
        spotDirection[0] = auxVec[0].toDouble();
        spotDirection[1] = auxVec[1].toDouble();
        spotDirection[2] = auxVec[2].toDouble();
    }
    if (json.contains("cosineCutoff") && json["cosineCutoff"].isDouble())
        spotCosineCutoff = json["cosineCutoff"].toDouble();
    if (json.contains("exponent") && json["exponent"].isDouble())
        spotExponent = json["exponent"].toDouble();

}

//! [1]
void SpotLight::write(QJsonObject &json) const
{
    Light::write(json);
    QJsonArray auxPos;
    auxPos.append(position[0]);auxPos.append(position[1]);auxPos.append(position[2]);
    json["position"] = auxPos;

    QJsonArray auxDir;
    auxDir.append(position[0]);auxDir.append(position[1]);auxDir.append(position[2]);
    json["direction"] = auxDir;

    json["cosineCutoff"] = spotCosineCutoff;
    json["exponent"] = spotExponent;

}
//! [1]

void SpotLight::print(int indentation) const
{
    const QString indent(indentation * 2, ' ');

    QTextStream(stdout) << "Spot Light" << "\n";
    QTextStream(stdout) << indent + 2 << "position:\t" << position[0] << ", "<< position[1] << ", "<< position[2] << "\n";
    QTextStream(stdout) << indent + 2 << "direction:\t" << spotDirection[0] << ", "<< spotDirection[1] << ", "<< spotDirection[2] << "\n";
    QTextStream(stdout) << indent + 2 << "cosineCutoff:\t" << spotCosineCutoff << "\n";
    QTextStream(stdout) << indent + 2 << "exponent:\t" << spotExponent << "\n";
}

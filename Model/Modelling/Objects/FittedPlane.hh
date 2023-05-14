#pragma once

#include <vector>
#include <string>
#include <limits>

#include <QString>
#include <QFile>
#include <QRegularExpression>

#include <iostream>
#include <stdlib.h>
#include <cstring>

#include "Object.hh"

using namespace std;

class FittedPlane: public Object
{
public:
    FittedPlane();

    // Constructor a partir de pmin i pmax (extrems del pla afitat)
    FittedPlane(vec2 pmin, vec2 pmax);  // suposarem sempre z = 0

    // Metodes de Object
    virtual bool hit(Ray& r, float tmin, float tmax, HitInfo& info) const override;
    virtual void aplicaTG(shared_ptr<TG>) override;
    virtual void read (const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;

protected:
    vector<vec4> vertexs[4]; // els 4 vèrtexs del pla afitat (no repetits)
    //vector<vec4> normalsVertexs[4]; // normals de l'objecte sense repetits
private:
    vec2 pmin;
    vec2 pmax;
};


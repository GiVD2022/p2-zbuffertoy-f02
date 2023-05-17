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
    FittedPlane(vec3 pmin, vec3 pmax);  // suposarem sempre z = 0
    FittedPlane(const QString &fileName);

    // Metodes de Object
    virtual bool hit(Ray& r, float tmin, float tmax, HitInfo& info) const override;
    virtual void aplicaTG(shared_ptr<TG>) override;
    virtual void read (const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;

    vec3 getPmin() { return pmin; } // més eficient declarar-los aquí??
    vec3 getPmax() { return pmax; }

protected:
    vec4 vertices[4]; // els 4 extrems del pla, es constueixen a partir dels pmin i pmax
    vec4 normal; // there is only one

    vec3 pmin;
    vec3 pmax;

};


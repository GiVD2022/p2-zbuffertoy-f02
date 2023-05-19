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
#include "Face.hh"
#include "Model/Modelling/TG/ScaleTG.hh"
#include "Model/Modelling/TG/TranslateTG.hh"

using namespace std;

class Mesh : public Object
{
public:
    Mesh() {};
    Mesh(const QString &fileName);

    virtual bool hit( Ray& r, float tmin, float tmax, HitInfo& info) const override;

    virtual void aplicaTG(shared_ptr<TG> tg) override;

    virtual void read (const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;

    virtual ~Mesh();

protected:
    QString nom;
    vector<Face> cares; // faces o cares de l'objecte
    vector<vec4> vertexs; // vertexs de l'objecte sense repetits
    vector<vec4> normalsVertexs; // normals de l'objecte sense repetits
    vector<vec2> textVertexs; // coordenades de textures sense repetits
private:
    void load(QString filename);
    void makeTriangles();
};


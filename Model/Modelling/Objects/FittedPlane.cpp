#include "FittedPlane.hh"

FittedPlane::FittedPlane()
{
    pmin = vec3(0.0);
    pmax = vec3(1.0, 1.0, 0.0);
}

FittedPlane::FittedPlane(const QString &fileName): Object()
{
    // what should i do?
}

FittedPlane::FittedPlane(vec3 pmin, vec3 pmax)
{
    pmin = pmin;
    pmax = pmax;

    float eps = 0.000001;
    if (fabs(pmin.x - pmax.x) < eps)
    {
        // "subpla" del pla {x = pmin.x}
        vertices[0] = vec4(pmin.x, pmin.y, pmin.z, 1.0);
        vertices[1] = vec4(pmin.x, pmax.y, pmin.z, 1.0);
        vertices[2] = vec4(pmin.x, pmax.y, pmax.z, 1.0);
        vertices[3] = vec4(pmin.x, pmin.y, pmin.z, 1.0);

        normal = vec4(1.0, 0.0, 0.0, 0.0);
    } else if (fabs(pmin.y - pmax.y) < eps)
    {
        // "subpla" del pla {y = pmin.y}
        vertices[0] = vec4(pmin.x, pmin.y, pmin.z, 1.0);
        vertices[1] = vec4(pmax.x, pmin.y, pmin.z, 1.0);
        vertices[2] = vec4(pmax.x, pmin.y, pmax.z, 1.0);
        vertices[3] = vec4(pmin.x, pmin.y, pmin.z, 1.0);

        normal = vec4(0.0, 1.0, 0.0, 0.0);

    } else if (fabs(pmin.z - pmax.z) < eps)
    {
        // "subpla" del pla {z = pmin.z}
        vertices[0] = vec4(pmin.x, pmin.y, pmin.z, 1.0);
        vertices[1] = vec4(pmax.x, pmin.y, pmin.z, 1.0);
        vertices[2] = vec4(pmax.x, pmax.y, pmin.z, 1.0);
        vertices[3] = vec4(pmin.x, pmax.y, pmin.z, 1.0);

        normal = vec4(0.0, 0.0, 1.0, 0.0);
    }
}

// Metodes de Object
bool FittedPlane::hit(Ray& r, float tmin, float tmax, HitInfo& info) const
{
    return false;
}
void FittedPlane::aplicaTG(shared_ptr<TG>)
{
    // TODO
}
void FittedPlane::read (const QJsonObject &json)
{
    if (json.contains("pmin") && json["pmin"].isArray()) {
        QJsonArray auxVec = json["pmin"].toArray();
        pmin[0] = auxVec[0].toDouble();
        pmin[1] = 0.0; // es llegeixen components x i z, la y se suposa plana
        pmin[2] = auxVec[1].toDouble();
    }
    if (json.contains("pmax") && json["pmax"].isArray()) {
        QJsonArray auxVec = json["pmax"].toArray();
        pmax[0] = auxVec[0].toDouble();
        pmax[1] = 0.0;
        pmax[2] = auxVec[1].toDouble();
    }
    Object::read(json);
}
void FittedPlane::write(QJsonObject &json) const
{   // s'escriuen components x i z, la y se suposa plana
    json["pmin"] = QJsonArray({ pmin.x, pmin.z });
    json["pmax"] = QJsonArray({ pmax.x, pmax.z });
}
void FittedPlane::print(int indentation) const
{
    const QString indent(indentation * 2, ' ');

    QTextStream(stdout) << indent << "pmin:\t" << pmin.x << ", "<< pmin.y << ", "<< pmin.z << "\n";
    QTextStream(stdout) << indent << "pmax:\t" << pmax.x << ", "<< pmax.y << ", "<< pmax.z << "\n";
}


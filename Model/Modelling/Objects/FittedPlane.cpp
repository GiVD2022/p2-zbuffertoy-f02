#include "FittedPlane.hh"

FittedPlane::FittedPlane()
{
    pmin = vec2(0.0);
    pmax = vec2(1.0, 1.0);
}

FittedPlane::FittedPlane(vec2 pmin, vec2 pmax)
{
    pmin = pmin;
    pmax = pmax;
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
        pmin[1] = auxVec[1].toDouble();
    }
    if (json.contains("pmax") && json["pmax"].isArray()) {
        QJsonArray auxVec = json["pmax"].toArray();
        pmax[0] = auxVec[0].toDouble();
        pmax[1] = auxVec[1].toDouble();
    }
}
void FittedPlane::write(QJsonObject &json) const
{
    json["pmin"] = QJsonArray({ pmin.x, pmin.y });
    json["pmax"] = QJsonArray({ pmax.x, pmax.y });
}
void FittedPlane::print(int indentation) const
{
    const QString indent(indentation * 2, ' ');

    QTextStream(stdout) << indent << "pmin:\t" << pmin.x << ", "<< pmin.y << "\n";
    QTextStream(stdout) << indent << "pmax:\t" << pmax.x << ", "<< pmax.y << "\n";
}


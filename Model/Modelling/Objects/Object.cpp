#include "Object.hh"

Object::Object()
{
    material = nullptr;
}


void Object::setMaterial(shared_ptr<Material> m) {
    material = m;
}

shared_ptr<Material> Object::getMaterial() {
    return material;
}

void Object::read (const QJsonObject &json)
{
    if (json.contains("material") && json["material"].isObject()) {
        QJsonObject auxMat = json["material"].toObject();
        if (auxMat.contains("type") && auxMat["type"].isString()) {
            QString tipus = auxMat["type"].toString().toUpper();
            MaterialFactory::MATERIAL_TYPES t = MaterialFactory::getInstance().getMaterialType(tipus);
            material = MaterialFactory::getInstance().createMaterial(t);
            material->read(auxMat);
        }

    }

    if (json.contains("name") && json["name"].isString())
        name = json["name"].toString();
}


//! [1]
void Object::write(QJsonObject &json) const
{
    json["name"] = name;

    QJsonObject materialObject;
    auto  value = MaterialFactory::getInstance().getIndexType (material);
    QString className = MaterialFactory::getInstance().getNameType(value);

    material->write(materialObject);
    materialObject["type"] = className;

    json["material"] = materialObject;
}
//! [1]

void Object::print(int indentation) const
{
    const QString indent(indentation * 2, ' ');

    QTextStream(stdout) << "Material:" << "\n";
    auto  value = MaterialFactory::getInstance().getIndexType (material);
    QString className = MaterialFactory::getInstance().getNameType(value);
    QTextStream(stdout) << indent << "type:\t" << className<<"\n";
    material->print(indentation+2);
}






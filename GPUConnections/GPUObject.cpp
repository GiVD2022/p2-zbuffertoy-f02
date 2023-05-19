#include "GPUObject.hh"

GPUObject::GPUObject()
{
    gpumaterial = make_shared<GPUMaterial>();
}

void GPUObject::read (const QJsonObject &json){
    Object::read(json);
    if(json.contains("material") && json["material"].isObject() ){
        QJsonObject auxMat = json["material"].toObject();
            if (auxMat.contains("type") && auxMat["type"].isString()) {
                QString tipus = auxMat["type"].toString().toUpper();
                gpumaterial->read(auxMat);
                qDebug() << gpumaterial->Ka.x <<" "<< gpumaterial->Ka.y <<" "<< gpumaterial->Ka.z  ;

            }
    }
}

GPUObject::~GPUObject() {

}

void GPUObject::print(int indentation) const {
    const QString indent(indentation * 2, ' ');

    QTextStream(stdout) << "Material:" << "\n";

    QTextStream(stdout) << indent << "type:\t" << "LAMBERTIAN"<<"\n";
    gpumaterial->print(indentation+2);
}

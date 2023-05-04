#include "GPUObject.hh"

GPUObject::GPUObject()
{
    gpumaterial = make_shared<GPUMaterial>();
}

void GPUObject::read (const QJsonObject &json){
    gpumaterial->read(json);
}

GPUObject::~GPUObject() {

}

void GPUObject::print(int indentation) const {
    const QString indent(indentation * 2, ' ');

    QTextStream(stdout) << "Material:" << "\n";

    QTextStream(stdout) << indent << "type:\t" << "LAMBERTIAN"<<"\n";
    gpumaterial->print(indentation+2);
}

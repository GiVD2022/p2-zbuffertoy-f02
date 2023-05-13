#include "GPUObject.hh"

GPUObject::GPUObject()
{
    gpumaterial = make_shared<GPUMaterial>();
}

void GPUObject::read (const QJsonObject &json){
    QTextStream(stdout) << "GPU Object READING:" << "\n";
    gpumaterial->read(json);
}

GPUObject::~GPUObject() {

}

void GPUObject::print(int indentation) const {
    QTextStream(stdout) << "GPU Object Pinting:" << "\n";

    const QString indent(indentation * 2, ' ');

    QTextStream(stdout) << "Material:\n";
    auto  value = GPUMaterialFactory::getInstance().getIndexType (gpumaterial);
    QString className = GPUMaterialFactory::getInstance().getNameType(value);
    QTextStream(stdout) << indent << "type:\t" << className<<"\n";
    gpumaterial->print(indentation+2);
}

#include "GPUObject.hh"

GPUObject::GPUObject()
{
    gpumaterial = make_shared<GPUMaterial>();
}

void GPUObject::read (const QJsonObject &json){
    QTextStream(stdout) << "GPU Object READING:" << "\n";
    Object::read(json);

    if(json.contains("material") && json["material"].isObject() ){
        QJsonObject auxMat = json["material"].toObject();
            if (auxMat.contains("type") && auxMat["type"].isString()) {
                QString tipus = auxMat["type"].toString().toUpper();
                gpumaterial->read(auxMat);
                qDebug() << gpumaterial->Ka.x <<" "<< gpumaterial->Ka.y <<" "<< gpumaterial->Ka.z  ;

            }
    }

    gpumaterial->read(json);

}

GPUObject::~GPUObject() {

}

void GPUObject::print(int indentation) const {
    QTextStream(stdout) << "GPU Object Printing:" << "\n";

    const QString indent(indentation * 2, ' ');
    QTextStream(stdout) << "Transformations:\n";
    if(scale){
        QTextStream(stdout) << indent << "type:\t" << "Scale"<<"\n";
    }
    if(translation){
        QTextStream(stdout) << indent << "type:\t" << "Translation"<<"\n";
    }
    QTextStream(stdout) << "Material:\n";
    auto  value = GPUMaterialFactory::getInstance().getIndexType (gpumaterial);
    QString className = GPUMaterialFactory::getInstance().getNameType(value);
    QTextStream(stdout) << indent << "type:\t" << className<<"\n";
    gpumaterial->print(indentation+2);
}

void GPUObject::setMaterial(shared_ptr<GPUMaterial> gpumat){
    gpumaterial = gpumat;
}


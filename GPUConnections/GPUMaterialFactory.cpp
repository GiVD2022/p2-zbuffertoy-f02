#include "GPUMaterialFactory.hh"

GPUMaterialFactory::GPUMaterialFactory()
{

}

shared_ptr<GPUMaterial> GPUMaterialFactory::createMaterial(MATERIAL_TYPES t) {
    shared_ptr<GPUMaterial> m;
    switch (t) {
    case LAMBERTIAN:
        m = make_shared<GPULambertian>();
        break;
    /*case METAL:
        m = make_shared<Metal>();
        break;
    case TRANSPARENT:
        m = make_shared<Transparent>();
        break;
    */
    case MATERIALTEXTURA:
        m = make_shared<GPUMaterialTextura>();
        break;
    default:
        break;
    }
    return m;
}

shared_ptr<GPUMaterial> GPUMaterialFactory::createMaterial(vec3 a, vec3 d, vec3 s, vec3 t, float beta, float opacity, float mu, MATERIAL_TYPES type) {
    shared_ptr<GPUMaterial> m;
    switch (type) {
    case LAMBERTIAN:
        m = make_shared<GPULambertian>(a, d, s, beta, opacity);
        break;
    /*case METAL:
        m = make_shared<Metal>(a,d,s,beta, opacity);
        break;
    case TRANSPARENT:
        // En principi nomes transparent fa servir l'index de refraccio i kt
        m = make_shared<Transparent>(a,d,s,t,beta, opacity,mu);
        break;
        */
    case MATERIALTEXTURA:
        m = make_shared<GPUMaterialTextura>(a,d,s,beta, opacity);
        break;
    default:
        break;
    }
    return m;
}

GPUMaterialFactory::MATERIAL_TYPES GPUMaterialFactory::getIndexType(shared_ptr<GPUMaterial> m) {
    if (dynamic_pointer_cast<GPULambertian>(m) != nullptr) {
        QTextStream(stdout) << "A\n";
        return MATERIAL_TYPES::LAMBERTIAN;
    } /*else if (dynamic_pointer_cast<Metal>(m) != nullptr) {
        return MATERIAL_TYPES::METAL;
    } else if (dynamic_pointer_cast<Transparent>(m) != nullptr) {
        return MATERIAL_TYPES::TRANSPARENT;
    }*/
    else if (dynamic_pointer_cast<MaterialTextura>(m) != nullptr) {
        QTextStream(stdout) << "B\n";
        return MATERIAL_TYPES::MATERIALTEXTURA;
    } else if (dynamic_pointer_cast<GPUMaterialTextura>(m) != nullptr) {
        QTextStream(stdout) << "C\n";
        return MATERIAL_TYPES::MATERIALTEXTURA;
    }
    QTextStream(stdout) << "D\n";
    return MATERIAL_TYPES::LAMBERTIAN;
}

GPUMaterialFactory::MATERIAL_TYPES GPUMaterialFactory::getMaterialType( QString name) {
    if (name=="LAMBERTIAN") return MATERIAL_TYPES::LAMBERTIAN;
    else if (name=="METAL") return MATERIAL_TYPES::METAL;
    else if (name=="TRANSPARENT") return MATERIAL_TYPES::TRANSPARENT;
    else if (name=="MATERIALTEXTURA") return MATERIAL_TYPES::MATERIALTEXTURA;
    else return  MATERIAL_TYPES::LAMBERTIAN;
}

QString GPUMaterialFactory::getNameType(MATERIAL_TYPES t)
{
    switch(t) {
    case LAMBERTIAN:
        return(QString("LAMBERTIAN"));
        break;
    case METAL:
        return(QString("METAL"));
        break;
    case TRANSPARENT:
        return(QString("TRANSPARENT"));
        break;
    case MATERIALTEXTURA:
        return(QString("MATERIALTEXTURA"));
        break;
    default:
        return(QString("LAMBERTIAN"));
        break;
    }
}

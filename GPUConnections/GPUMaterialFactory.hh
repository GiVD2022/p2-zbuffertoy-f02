#pragma once

#include "GPUMaterial.hh"
#include "GPULambertian.hh"
//#include "ToonMaterial.hh"
//#include "Transparent.hh"
#include "GPUMaterialTextura.hh"
//#include "Metal.h"

class GPUMaterialFactory
{
public:
    GPUMaterialFactory();
public:
    typedef enum  MATERIAL_TYPES{
        LAMBERTIAN,
        METAL,
        TRANSPARENT,
        MATERIALTEXTURA,
    } MATERIAL_TYPES;

    static GPUMaterialFactory& getInstance() {
        static GPUMaterialFactory instance;
        return instance;
    }

    shared_ptr<GPUMaterial> createMaterial(MATERIAL_TYPES t);
    shared_ptr<GPUMaterial> createMaterial(vec3 a, vec3 d, vec3 s, vec3 t,float beta, float opacity, float mu, MATERIAL_TYPES type);
    MATERIAL_TYPES getIndexType (shared_ptr<GPUMaterial> m);
    MATERIAL_TYPES getIndexType (shared_ptr<Material> m);
    MATERIAL_TYPES getMaterialType( QString name);
    QString        getNameType(MATERIAL_TYPES  t);
};



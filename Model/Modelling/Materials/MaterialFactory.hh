#pragma once

#include "library/Singleton.hh"
#include "Material.hh"
#include "Lambertian.hh"


class MaterialFactory: public Singleton<MaterialFactory>
    {
        // needs to be friend in order to
        // access the private constructor/destructor
        friend class Singleton<MaterialFactory>;
    private:
        MaterialFactory() {}
        virtual ~MaterialFactory() {}
public:
    typedef enum  MATERIAL_TYPES{
        LAMBERTIAN,
        METAL,
        TRANSPARENT,
        MATERIALTEXTURA,
    } MATERIAL_TYPES;


    shared_ptr<Material> createMaterial(MATERIAL_TYPES t);
    shared_ptr<Material> createMaterial(vec3 a, vec3 d, vec3 s, float beta, float opacity, MATERIAL_TYPES t);
    MATERIAL_TYPES getIndexType (shared_ptr<Material> m);
    MATERIAL_TYPES getMaterialType( QString name);
    QString        getNameType(MATERIAL_TYPES  t);

};

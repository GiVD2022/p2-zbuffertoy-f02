#ifndef GPUMATERIALTEXTURA_HH
#define GPUMATERIALTEXTURA_HH
#include "Model/Modelling/Materials/MaterialTextura.hh"
#include "GPUMaterial.hh"


class GPUMaterialTextura: public MaterialTextura, public GPUMaterial
{
public:
    GPUMaterialTextura();
    GPUMaterialTextura(const vec3& color);
    GPUMaterialTextura(const vec3& a, const vec3& d, const vec3& s, const float k);
    GPUMaterialTextura(const vec3& a, const vec3& d, const vec3& s, const float k, const float o);
};

#endif // GPUMATERIALTEXTURA_HH

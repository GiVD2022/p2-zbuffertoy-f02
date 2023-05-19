#include "GPUMaterialTextura.hh"

GPUMaterialTextura::GPUMaterialTextura()
{

}

GPUMaterialTextura::GPUMaterialTextura(const vec3& color): MaterialTextura(color), GPUMaterial()
{
}

GPUMaterialTextura::GPUMaterialTextura(const vec3& a, const vec3& d, const vec3& s, const float k):
    MaterialTextura(a, d, s, k){
}

GPUMaterialTextura::GPUMaterialTextura(const vec3& a, const vec3& d, const vec3& s, const float k, const float o):
    MaterialTextura(a, d, s, k, o), GPUMaterial(a, d, s, k, o) {
}

void GPUMaterialTextura::read(const QJsonObject &json){
    GPUMaterial::read(json);
    if (json.contains("textureFile") && json["textureFile"].isString())
        textura = make_shared<Texture>(json["textureFile"].toString());
}

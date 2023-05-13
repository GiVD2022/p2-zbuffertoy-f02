#pragma once
#include "Texture.hh"
#include "Material.hh"

class MaterialTextura: public Material
{
public:
    MaterialTextura() {};
    MaterialTextura(const vec3& color);
    MaterialTextura(const vec3& a, const vec3& d, const vec3& s, const float k);
    MaterialTextura(const vec3& a, const vec3& d, const vec3& s, const float k, const float o);
    virtual ~MaterialTextura();

    virtual bool scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray & r_out) const;
    virtual vec3 getDiffuse(vec2 uv) const;
    void read(const QJsonObject &json);

    void print(int indentation) const;

    shared_ptr<Texture> getTextura() const;

protected:
    shared_ptr<Texture> textura;
};

#include "Lambertian.hh"

Lambertian::Lambertian(const vec3& color): Material()
{
    Kd = color;
}

Lambertian::Lambertian(const vec3& a, const vec3& d, const vec3& s, const float k):
    Material(a, d, s, k) {
}

Lambertian::Lambertian(const vec3& a, const vec3& d, const vec3& s, const float k, const float o):
    Material(a, d, s, k, o) {
}
Lambertian::~Lambertian()
{
}

bool Lambertian::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray & r_out) const  {
    vec3 target = rec.p + rec.normal + Hitable::RandomInSphere();
    r_out =  Ray(rec.p, target-rec.p);
    color = Kd;
    //return true;
    return false;
}

vec3 Lambertian::getDiffuse(vec2 uv) const {
    return Kd;

}

#include "GPULambertian.hh"

GPULambertian::GPULambertian()
{

}

GPULambertian::GPULambertian(const vec3& color): Lambertian(color), GPUMaterial()
{
}

GPULambertian::GPULambertian(const vec3& a, const vec3& d, const vec3& s, const float k):
    Lambertian(a, d, s, k){
}

GPULambertian::GPULambertian(const vec3& a, const vec3& d, const vec3& s, const float k, const float o):
    Lambertian(a, d, s, k, o), GPUMaterial(a, d, s, k, o) {
}

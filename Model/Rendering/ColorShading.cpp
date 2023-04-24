#include "ColorShading.hh"


vec3 ColorShading::shading(shared_ptr<Scene> scene, HitInfo& info, vec3 lookFrom) {
    return info.mat_ptr->Kd;
}

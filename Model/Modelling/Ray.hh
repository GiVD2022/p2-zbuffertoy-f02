#pragma once
#include "library/Common.h"

class Ray {
  private:
    vec3 origin;
    vec3 direction;

  public:
    Ray() {}

    Ray(const vec3 &orig, const vec3 &dir, float t_min_=0.01f, float t_max_=std::numeric_limits<float>::infinity()):
      origin(orig),
      direction(dir)
    {}

    /* retorna el punt del raig en en temps/lambda t */
    vec3 operator() (const float &t) const {
      return origin + direction*t;
    }

    vec3 getOrigin() const       { return origin; }
    vec3 getDirection() const    { return direction; }
    vec3 pointAtParameter(float t) const { return origin + t*direction; }

};


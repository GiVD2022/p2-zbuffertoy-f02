#pragma once

#include "Ray.hh"


using namespace std;
class Material;


class HitInfo
{
public:
    float     t;         // t del raig on s'ha intersecat
    vec3      p;         // punt del raig on hi ha la intersecció
    vec3      normal;    // normal en el punt d'intersecció
    Material *mat_ptr;   // material de l'objecte que s'ha intersectat
    vec2      uv;        // punt 2D per la projeccio de la textura

    HitInfo():
        t(std::numeric_limits<float>::infinity()),
        p(0.0f),
        normal(0.0f),
        mat_ptr(NULL),
        uv(0.0f)
        {}

    //  "operator =" per la classe  IntersectionInfo
    HitInfo &operator =(const HitInfo &rhs) {
      p = rhs.p;
      mat_ptr = rhs.mat_ptr;
      normal = rhs.normal;
      t = rhs.t;
      uv = rhs.uv;
      return *this;
    }
};

class Hitable
{
public:
    Hitable(){};
    ~Hitable(){};


    // Funcio que retorna la intersecció més propera al t_min del raig. La intersecció
    // estarà entre t_min i t_max
     virtual bool hit (Ray& r, float tmin, float tmax, HitInfo& info) const = 0;


    // OPCIONAL: Mètode que retorna totes les interseccions que es troben al llarg del raig
    //    virtual bool allHits(const Ray& r, vector<shared_ptr<HitInfo> infos) const = 0;

    // Metode que retorna un punt interior a una esfera de centre (0,0,0) i radi 1
    static vec3 RandomInSphere() {
        vec3 p;
        do {
            p = 2.0f*vec3(double(rand())/RAND_MAX, double(rand())/RAND_MAX,double(rand())/RAND_MAX) - vec3(1,1,1);
        } while (length(p) >=  1.0f);
        return p;
    }
};


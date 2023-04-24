#include "Scene.hh"

Scene::Scene()
{
    pmin.x = -1.0f;  pmin.y = -1.0f; pmin.z = -1.0f;
    pmax.x = 1.0f;  pmax.y = 1.0f; pmax.z = 1.0f;
    // Inicialització de la capsa minima
    capsaMinima.pmin = vec3(-1.0, -1.0,-1.0);
    capsaMinima.a = 2;
    capsaMinima.h = 2;
    capsaMinima.p = 2;
}
/**
 * @brief Scene::~Scene
 */
Scene::~Scene() {
    objects.clear();
}

bool Scene::hit(Ray &raig, float tmin, float tmax, HitInfo& info) const {
    // Pràctica 1: TODO FASE 0 i FASE 1:
    // Heu de codificar la vostra solucio per aquest metode substituint el 'return true'
    // Una possible solucio es cridar el mètode "hit" per a tots els objectes i quedar-se amb la interseccio
    // mes propera a l'observador, en el cas que n'hi hagi més d'una.
    // Si un objecte es intersecat pel raig, el parametre  de tipus HitInfo conte
    // la informació sobre la interseccio.
    // Cada vegada que s'intersecta un objecte s'ha d'actualitzar el HitInfo del raig.

    if (objects.size()>0) {
        return objects[0]->hit(raig, tmin, tmax, info);
    }
    return false;
}


void Scene::update(int nframe) {
    for (unsigned int i = 0; i< objects.size(); i++) {
        objects[i]->update(nframe);
    }
}

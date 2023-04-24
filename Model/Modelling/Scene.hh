#pragma once

#include <vector>
#include "Hitable.hh"
#include "Animation.hh"

#include "Objects/Object.hh"
#include "Objects/Mesh.hh"
#include "Materials/Material.hh"


using namespace std;
using namespace Common;

class Scene: public Hitable
{
public:
    typedef enum
    {
           VIRTUALWORLD,
           REALDATA,
           TEMPORALVW,
           TEMPORALDATA
    } DATA_TYPES;

    typedef enum
    {
        MATERIAL,
        COLORMAP
    } MATERIAL_TYPES;

    // AMPLIACIO: Posible objecte que no sigui un pla afitat: una esfera
    shared_ptr<Object> basePlane;

    QString name;

    // dimensions de l'escena virtual que es renderintza: capsa mínima contenidora
    vec3 pmin, pmax;
    // Capsa contenedora de l'escena
    Capsa3D capsaMinima;

    // Vector d'objectes continguts a l'escena
    std::vector<shared_ptr<Object>> objects;

    std::vector<shared_ptr<Object>> getObjects() {return objects;}

    Scene();

    // TODO: Fase 1
    // Constructora a utilitzar quan s'inicialitza una escena amb un pla base o
    // una esfera base
    Scene(shared_ptr<Object> base);

    virtual ~Scene();

    // Funcio que calcula la interseccio del raig r amb l'escena. Guarda la informacio
    // del punt d'interseccio més proper a t_min del Raig, punt que està entre t_min i t_max del Raig.
    // Retorna cert si existeix la interseccio, fals, en cas contrari
    virtual bool hit(Ray& raig, float tmin, float tmax, HitInfo& info) const override;



    // OPCIONAL: Mètode que retorna totes les interseccions que es troben al llarg del raig
    //    virtual bool allHits(const Ray& r, vector<shared_ptr<HitInfo> infos) const = 0;

    void update(int nframe);

};


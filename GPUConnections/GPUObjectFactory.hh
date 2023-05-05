#pragma once

#include "Model/Modelling/Objects/ObjectFactory.hh"
#include "GPUConnections/GPUMesh.hh"

class GPUObjectFactory: public Singleton<GPUObjectFactory>
{
    // needs to be friend in order to
    // access the private constructor/destructor
    friend class Singleton<GPUObjectFactory>;
private:
    GPUObjectFactory() {}
    virtual ~GPUObjectFactory() {}
public:

    virtual shared_ptr<GPUObject> createObject(ObjectFactory::OBJECT_TYPES t);

    // Crea un objecte gizmo per una data concreta
    virtual shared_ptr<GPUObject> createObject(  QString s, ObjectFactory::OBJECT_TYPES t);

};

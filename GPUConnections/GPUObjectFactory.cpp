#include "GPUObjectFactory.hh"

// TODO Fase 1: Crea objectes de més tipus
// Trobaràs l'enumeració d'OBJECT_TYPES en el fitxer FactoryObject.hh
shared_ptr<GPUObject> GPUObjectFactory::createObject(ObjectFactory::OBJECT_TYPES t)
{
    shared_ptr<GPUObject> o;
    switch (t) {
    case ObjectFactory::OBJECT_TYPES::MESH:
        o = make_shared<GPUMesh>();
        break;
    case ObjectFactory::OBJECT_TYPES::FITTEDPLANE:
        o = make_shared<GPUFittedPlane>();
        break;
    case ObjectFactory::OBJECT_TYPES::SPHERE:
        o = make_shared<GPUMesh>("://resources/models/sphere0.obj");
        break;
    default:
        break;
    }

    return o;
}

shared_ptr<GPUObject> GPUObjectFactory::createObject( QString s, ObjectFactory::OBJECT_TYPES t) {
    shared_ptr<GPUObject> o;
    switch (t) {
    case ObjectFactory::OBJECT_TYPES::MESH:
        o = make_shared<GPUMesh>(s);
        break;
    default:
        break;
    }

    return o;
}

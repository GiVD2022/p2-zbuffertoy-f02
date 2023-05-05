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

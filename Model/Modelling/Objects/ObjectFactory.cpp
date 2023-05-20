#include "ObjectFactory.hh"

// TODO Fase 1: Crea objectes de més tipus
// Trobaràs l'enumeració d'OBJECT_TYPES en el fitxer FactoryObject.hh
shared_ptr<Object> ObjectFactory::createObject(OBJECT_TYPES t)
{
    shared_ptr<Object> o;
    switch (t) {
    case MESH:
        o = make_shared<Mesh>();
        break;
    default:
        break;
    }

    return o;
}

shared_ptr<Object> ObjectFactory::createObject( QString s, OBJECT_TYPES t) {
    shared_ptr<Object> o;
    switch (t) {
    case MESH:
        o = make_shared<Mesh>(s);
        break;
    default:
        break;
    }

    return o;
}

ObjectFactory::OBJECT_TYPES ObjectFactory::getIndexType(shared_ptr<Object> l) {
    if (dynamic_pointer_cast<Mesh>(l) != nullptr) {
        return OBJECT_TYPES::MESH;
    }

    return OBJECT_TYPES::MESH;
}

ObjectFactory::OBJECT_TYPES ObjectFactory::getObjectType( QString name) {
    if (name=="MESH") return OBJECT_TYPES::MESH;
    else if (name=="BOX") return OBJECT_TYPES::BOX;
    else if (name=="FITTEDPLANE") return OBJECT_TYPES::FITTEDPLANE;
    else return  OBJECT_TYPES::MESH;
}

QString ObjectFactory::getNameType(int t)
{
    switch(t) {
    case BOX:
        return(QString("BOX"));
        break;
    case MESH:
        return(QString("MESH"));
        break;
    case FITTEDPLANE:
        return(QString("FITTEDPLANE"));
        break;
    default:
        return(QString("SPHERE"));
        break;
    }
}

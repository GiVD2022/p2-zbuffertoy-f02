#pragma once

#include "library/Singleton.hh"
#include "Object.hh"
#include "Mesh.hh"


class ObjectFactory : public Singleton<ObjectFactory>
{
    // needs to be friend in order to
    // access the private constructor/destructor
    friend class Singleton<ObjectFactory>;
private:
    ObjectFactory() {}
    virtual ~ObjectFactory() {}
public:
    typedef enum  {
        BOX,
        MESH,
        FITTEDPLANE
    } OBJECT_TYPES;

    virtual shared_ptr<Object> createObject(OBJECT_TYPES t);

    // Crea un objecte gizmo per una data concreta
    // FASE 1: Cal incloure la translació i l'escalat per a poder escalar l'objecte sogon el valor de la dada
    virtual shared_ptr<Object> createObject(  QString s,  OBJECT_TYPES t);

    OBJECT_TYPES getIndexType (shared_ptr<Object> l);
    OBJECT_TYPES getObjectType(QString name);
    QString      getNameType(int  t);
};


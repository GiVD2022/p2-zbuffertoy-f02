#pragma once

#include <string.h>
#include <QString>

#include "DataInOut/Serializable.hh"
#include "GPUConnections/GPUScene.hh"


class GPUSceneFactory: public Serializable
{
public:
    typedef enum
    {
           VIRTUALWORLD,
           REALDATA,
           TEMPORALVW
    } SCENE_TYPES;

    GPUSceneFactory() {};
    virtual ~GPUSceneFactory() {};

    virtual shared_ptr<GPUScene> createScene() = 0;
    virtual shared_ptr<GPUScene> createScene(QString nomFitxer) = 0;

    static SCENE_TYPES getSceneFactoryType( QString name);
    QString            getNameType(SCENE_TYPES t) const;

protected:
    shared_ptr<GPUScene> scene;
    SCENE_TYPES currentType;

};



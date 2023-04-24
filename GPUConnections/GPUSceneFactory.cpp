#include "GPUConnections/GPUSceneFactory.hh"


GPUSceneFactory::SCENE_TYPES GPUSceneFactory::getSceneFactoryType( QString name) {
    if (name=="VIRTUALWORLD") return SCENE_TYPES::VIRTUALWORLD;
    else if (name=="REALDATA") return SCENE_TYPES::REALDATA;
    else if (name=="TEMPORALVW") return SCENE_TYPES::TEMPORALVW;
    else return  SCENE_TYPES::VIRTUALWORLD;
}

QString GPUSceneFactory::getNameType(SCENE_TYPES t) const
{
    switch(t) {
    case VIRTUALWORLD:
        return(QString("VIRTUALWORLD"));
        break;
    case REALDATA:
        return(QString("REALDATA"));
        break;
    case TEMPORALVW:
        return(QString("TEMPORALVW"));
        break;
    default:
        return(QString("VIRTUALWORLD"));
        break;
    }
}

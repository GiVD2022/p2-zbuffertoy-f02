#pragma once

#include "Model/Modelling/Materials/ColorMapStatic.hh"
#include "Model/Modelling/Materials/Material.hh"

#include "DataInOut/VisualMapping.hh"

#include "GPUConnections/GPUSceneFactory.hh"
#include "GPUConnections/GPUObjectFactory.hh"
#include "GPUConnections/GPUScene.hh"
#include "GPUFittedPlane.hh"
#include "Model/Modelling/TG/TranslateTG.hh"
#include "Model/Modelling/TG/ScaleTG.hh"

// TODO Pràctica 2: Fase 1 construir la Factoria de Materials
//#include "GPUConnections/GPUMaterialFactory.hh"

class GPUSceneFactoryData: public GPUSceneFactory
{
public:
    GPUSceneFactoryData(){};
    GPUSceneFactoryData(shared_ptr<VisualMapping> mr);

    shared_ptr<GPUScene>  createScene(QString nomFitxer) override;
    shared_ptr<GPUScene>  createScene() override;

protected:
    // dades: vector de parells <AttributeMapping, vector de dades d'aquella propietat>
    vector<pair<QString, vector<vec3>>> dades;
    shared_ptr<VisualMapping> mapping;

    virtual void read (const QJsonObject &json) override;
    virtual void write (QJsonObject &json) const override;
    virtual void print (int indentation) const override;

    bool load (QString nameFile);
    bool save (QString nameFile) const;

    vec3 getPuntBase(ObjectFactory::OBJECT_TYPES gyzmo, vec2 puntReal);

    void readData(const QJsonObject &json);
    void writeData (QJsonObject &json, int i) const ;

    shared_ptr<GPUScene>    visualMaps();
    virtual shared_ptr<GPUMesh>   objectMaps(int i, int j);
    // TODO: Pràctica 2: Fase 1
    // virtual shared_ptr<GPUMaterial> materialMaps(int i, int j);

};


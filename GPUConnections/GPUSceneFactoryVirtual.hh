#pragma once


#include "GPUConnections/GPUSceneFactory.hh"
#include "GPUConnections/GPUObjectFactory.hh"
#include "GPUConnections/GPUScene.hh"


class GPUSceneFactoryVirtual : public GPUSceneFactory
{
public:
    GPUSceneFactoryVirtual() {};

    shared_ptr<GPUScene>  createScene (QString nomFitxer) override;
    shared_ptr<GPUScene>  createScene() override;

    virtual void read(const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;

    bool load(QString nameFile);
    bool save(QString nameFile) const;

};


#pragma once

#include "DataInOut/Serializable.hh"
#include "Model/Modelling/Objects/ObjectFactory.hh"
#include "Model/Modelling/Materials/ColorMapStatic.hh"
#include "Model/Modelling/Materials/MaterialFactory.hh"

class AttributeMapping : public Serializable
{
public:
    AttributeMapping();
    virtual ~AttributeMapping() {};
    virtual void read (const QJsonObject &json) override;
    virtual void write (QJsonObject &json) const override;
    virtual void print (int indentation) const override;

    QString name;

    float minValue;
    float maxValue;

    ObjectFactory::OBJECT_TYPES gyzmo;
    shared_ptr<Material> material;
    ColorMapStatic::COLOR_MAP_TYPES colorMapType;

};

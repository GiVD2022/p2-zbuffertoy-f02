#pragma once


#include <QFile>
#include <QTextStream>
#include <iostream>
#include <sstream>
#include <QObject>
#include <QString>
#include <QStringList>

#include <vector>
#include "Model/Modelling/Scene.hh"
#include "Model/Modelling/Objects/ObjectFactory.hh"
#include "Model/Modelling/Materials/ColorMapStatic.hh"
#include "Model/Modelling/Materials/Texture.hh"
#include "Model/Modelling/Materials/MaterialFactory.hh"
#include "DataInOut/AttributeMapping.hh"

/* VisualMapping
 * Classe que guarda les dimensions del mon real i del mon virtual per
 * i les informació de les dades
 * per a cada propietat guarda les seves caracteristiques a propInfo i
 * el vector de les dades mostrejades d'aquella propietat
 * per a cada dada mostrejada es te (coordenadaX, coordenadaZ, valor)
 * con les coordenades es suposen mostrejades en un mapa
*/

class VisualMapping: public Serializable {
public:
    VisualMapping() {};

    virtual void read(const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;

    virtual ~VisualMapping() {};

    float                      Rxmin, Rxmax, Rzmin, Rzmax;
    float                      Vxmin, Vxmax, Vymin, Vymax, Vzmin, Vzmax;
    vector<AttributeMapping *> attributeMapping;

    void writeAttribute(QJsonObject &attributeJson, int i) const;
    void readAttribute(const QJsonObject &json);
    void printAttribute(int i, int indentation) const;
};


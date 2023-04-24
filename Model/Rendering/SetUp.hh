#pragma once

#include <QFile>
#include "DataInOut/Serializable.hh"
#include "Model/Modelling/Lights/LightFactory.hh"

#include "Model/Rendering/ShadingFactory.hh"
#include "Model/Rendering/ShadingStrategy.hh"
#include "Model/Rendering/ColorShading.hh"

class SetUp : public Serializable
{
public:
    SetUp();

    QString                         getOutputFile();
    vec3                            getGlobalLight();
    std::vector<shared_ptr<Light>>  getLights();
    shared_ptr<ShadingStrategy>     getShadingStrategy() {return shade;}
    bool                            getBackground();
    vec3                            getTopBackground();
    vec3                            getDownBackground();
    int                             getMAXDEPTH();
    int                             getSamples();
    bool                            getReflections() {return reflections;}
    bool                            getRefractions() {return refractions;}
    bool                            getShadows() {return shadows;}
    bool                            getTextures() {return textures;}


    void setOutpuFile(QString name);
    void setGlobalLight(vec3 globalLight);
    void setShadingStrategy(shared_ptr<ShadingStrategy> s) {shade = s;}
    void setBackground(bool back);
    void setTopBackground(vec3 color);
    void setDownBackground(vec3 color);
    void setSamples(int s);
    void setReflections(bool b);
    void setRefractions(bool b);
    void setShadows(bool b);
    void setTextures(bool b);

    virtual void read (const QJsonObject &json) override;
    virtual void write (QJsonObject &json) const override;
    virtual void print (int indentation) const override;

    bool load( QString nameFile);
    bool save( QString nameFile) const;

    virtual ~SetUp() {};


private:
    QString outputFile;

    // Shading utilitzat
    shared_ptr<ShadingStrategy> shade;

    // Conté si s'ha de tenir en compte el background o no en els rajos secundaris en
    // cas de no fer hit amb l'escena
    bool background = false;
    // colors top i bottom de  fons
    vec3 topBackground;
    vec3 downBackground;

    // màxim nombre de rajos recursius incloent el primari
    int   MAXDEPTH;

    // number of samples per pixels
    int   numSamples;

    // flags per activar funcionalitats del RayColor
    // Pràctica 1: FASE 2: cal usar-los allà
     bool reflections;
     bool refractions;
     bool shadows;
     bool textures;

     // Pràctica 1: FASE 2: Guarda si en les iteracions recursives de rayColor() en cas de no haver-hi hit
     // s'utilitza el color de background o la llum ambient global
     // bool backgroundInRecurvise = false;

};


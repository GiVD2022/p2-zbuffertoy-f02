#pragma once

#include <QtWidgets>
#include "Controller.hh"
#include "GPUConnections/GPUMesh.hh"
#include "GPUConnections/GPUSceneFactory.hh"

class GLBuilder : public QObject {
    Q_OBJECT

public:
    GLBuilder(){};


public slots:
    void newObjFromFile();
    void newVirtualScene();
    void newDataScene();
    void loadSettings();


signals:
     void settingsChanged();
     void newObj(shared_ptr<GPUMesh> o);
     void newScene();
};


#pragma once

#include <QString>

#include "GPUConnections/GPUSceneFactory.hh"
#include "GPUConnections/GPUSceneFactoryVirtual.hh"
#include "GPUConnections/GPUSceneFactoryData.hh"
#include "GPUConnections/GPUSetUp.hh"

class Controller
{
private:
    shared_ptr<GPUScene>  scene;
    shared_ptr<GPUSetUp>  visualSetup;

    static Controller* // Singleton

    // static pointer which will points to the instance of this class
    instancePtr;

    // Default constructor
    Controller();

public:

    // deleting copy constructor
    Controller(const Controller& obj)
        = delete;

    static Controller* getInstance() {
        // If there is no instance of class
        // then we can create an instance.
        if (instancePtr == NULL) {
          // We can access private members
          // within the class.
          instancePtr = new Controller();

          // returning the instance pointer
          return instancePtr;
        } else {
          // if instancePtr != NULL that means
          // the class already have an instance.
          // So, we are returning that instance
          // and not creating new one.
          return instancePtr;
        }
      }


    shared_ptr<GPUScene>  getScene() {return scene; }
    shared_ptr<GPUSetUp>  getSetUp() {return visualSetup; }

    void setScene (shared_ptr<GPUScene> s) {  scene = s;}
    void setSetUp (shared_ptr<GPUSetUp> v) {  visualSetup = v;}

    bool createScene(GPUSceneFactory::SCENE_TYPES currentType, QString name);
    bool createScene();
    bool createScene(int nFrames);

    bool createSettings(QString name);
    bool createShading(ShadingFactory::SHADING_TYPES t);

    void update(int i);
};

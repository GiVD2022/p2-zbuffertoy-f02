#include "Controller.hh"

Controller::Controller()
{
    scene = make_shared<GPUScene>();
    // Valors per defecte de visualSetup
    visualSetup = make_shared<GPUSetUp>();
}


bool Controller::createScene(GPUSceneFactory::SCENE_TYPES currentType, QString name) {
    shared_ptr<GPUSceneFactory> sf = nullptr;
    switch (currentType)  {
    case GPUSceneFactory::SCENE_TYPES::VIRTUALWORLD:
        sf = make_shared<GPUSceneFactoryVirtual>();
        break;
    case GPUSceneFactory::SCENE_TYPES::REALDATA:
        sf = make_shared<GPUSceneFactoryData>();
        break;
    case GPUSceneFactory::SCENE_TYPES::TEMPORALVW:
        // TO DO opcional:  Afegir les factories de escenes temporals amb les animacions
        return false;
      break;
    default:
        break;
    }
    scene = sf->createScene(name);
    return (scene != nullptr);
}


bool Controller::createScene() {
    //TODO: Pots posar codi per a fer una escena amb multiples objectes des de codi, si vols

    return true;
}

bool Controller::createScene(int nFrames) {

    //TO DO Fase 3 opcional: Codi exemple amb animacions però que es pot canviar
    // pel que creguis convenient

    auto mesh = make_shared<GPUMesh>("://cub.obj");
    mesh->setMaterial(make_shared<Lambertian>(vec3(0.5, 0.2, 0.7)));

    shared_ptr<Animation> anim = make_shared<Animation>();
    // anim->transf =  make_shared<TranslateTG>(vec3(0.2));
    mesh->addAnimation(anim);

    return true;
}
bool Controller::createSettings(QString name) {
    // Create Settings and set them to the scene
    visualSetup = make_shared<GPUSetUp>();
    if (visualSetup->load(name) ) {
        visualSetup->print(0);
        return (true);
    }
    return false;
}

void Controller::update(int i) {
    scene->update(i);
}

#include "ViewGL/GLBuilder.hh"

void GLBuilder::newObjFromFile()
{
    QString fileName = QFileDialog::getOpenFileName();
    if (!fileName.isNull()) {
            // OJO! El primer paràmetre de la constructora de l'Object és el número de punts del model.
            // Si l'objecte té més punts en el .bj, cal canviar aquest valor
            shared_ptr<GPUMesh> obj = make_shared<GPUMesh>(100000, fileName);
            auto scene = Controller::getInstance()->getScene();
            scene->addObject(obj);
            shared_ptr<GPUCamera> camera = dynamic_pointer_cast<GPUCamera>(Controller::getInstance()->getSetUp()->getCamera());
            camera->actualitzaCamera(scene->capsaMinima);
            emit newObj(obj);
    }
}

void GLBuilder::newVirtualScene()
{
    QString fileName = QFileDialog::getOpenFileName();
    if (!fileName.isNull()) {
        QMessageBox msgBox;
        if(Controller::getInstance()->createScene(GPUSceneFactory::SCENE_TYPES::VIRTUALWORLD, fileName)) {
            msgBox.setText("Virtual Scene well loaded.");
            emit newScene();
        }
        else msgBox.setText("Scene NOT loaded. Error reading data.");
        msgBox.exec();
    }
}


void GLBuilder::newDataScene()
{
    QString fileName = QFileDialog::getOpenFileName();
    if (!fileName.isNull()) {
        QMessageBox msgBox;
        if (Controller::getInstance()->createScene(GPUSceneFactory::SCENE_TYPES::REALDATA, fileName)) {
                msgBox.setText("Data Scene well loaded.");
                emit newScene();
        } else msgBox.setText("Scene NOT loaded. Error reading data.");
        msgBox.exec();
    }
}

// Metode no usat en la pràctica 2 base. Es pot usar opcional si es vol carregar el setup
// Cal modificar-lo per adaptar-lo a la pràctica 2, si fos necessari
void GLBuilder::loadSettings() {
    QString fileName = QFileDialog::getOpenFileName();
    if (!fileName.isNull()) {
        QMessageBox msgBox;
        if (Controller::getInstance()->createSettings(fileName)) {
                msgBox.setText("Visual Settings well loaded.");

        } else msgBox.setText("Settings NOT loaded. Error reading data.");
        msgBox.exec();
        emit settingsChanged();
    }
}



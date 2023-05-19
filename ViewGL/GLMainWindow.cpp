
#include "ViewGL/GLMainWindow.hh"

GLMainWindow::GLMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainTabs->setCurrentIndex(0);

    // Codi necessari per adaptar el projecte a la versio 330 de gl
    QGLFormat glfModern=QGLFormat::defaultFormat();
    glfModern.setVersion(3,3);
    glfModern.setProfile(QGLFormat::CoreProfile);
    glfModern.setSampleBuffers(true);
    glfModern.setSwapInterval(0);
    glfModern.setDefaultFormat(glfModern);
    glWidget = new GLWidget(glfModern);

    setCentralWidget(ui->centralWidget);

    ui->gridLayout_2->addWidget(glWidget, 0, 0);
    changes = true;


    // Construcció del Builder
    builder = new GLBuilder();

    setWindowTitle(tr("Pràctica 2: ZbufferToy - 2022-23"));
    changes = true;

    // connexio dels menus amb els mètodes corresponents

    connect(ui->action_obre_fitxer, SIGNAL(triggered()), builder, SLOT(newObjFromFile()));
    connect(ui->action_obre_escena, SIGNAL(triggered()), builder, SLOT(newVirtualScene()));
    connect(ui->action_obre_dades, SIGNAL(triggered()), builder, SLOT(newDataScene()));

    // connect(ui->actionLoadSetUp, SIGNAL(triggered()), builder, SLOT(loadSettings()));
    // connect(builder, SIGNAL(settingsChanged()), this, SLOT(refreshWindow()));


    connect(ui->action_save_frame_as_image, SIGNAL(triggered()), glWidget, SLOT(saveImage()));
    connect(ui->action_start_and_save_animation, SIGNAL(triggered()), glWidget, SLOT(saveAnimation()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(aboutMenu()));

    // Connexió de les opcions de menús
    connectShaders();

    // Sincronització del canvi de paràmetres de la camera amb el ratolí
    connect(glWidget, SIGNAL(ObsCameraChanged(shared_ptr<GPUCamera>)), this, SLOT(setObsCamera(shared_ptr<GPUCamera>)));
    connect(glWidget, SIGNAL(FrustumCameraChanged(shared_ptr<GPUCamera>)), this, SLOT(setFrustumCamera(shared_ptr<GPUCamera>)));

    connect(builder, SIGNAL(newObj(shared_ptr<GPUMesh>)), glWidget, SLOT(updateObject(shared_ptr<GPUMesh>)));
    connect(builder, SIGNAL(newScene()), glWidget, SLOT(updateScene()));

}


GLMainWindow::~GLMainWindow()
{
    delete builder;
    delete ui;
}


void GLMainWindow::aboutMenu() {
    QDialog dialog;
    Ui::dialogAbout ui;
    ui.setupUi(&dialog);

    dialog.show();
    dialog.exec();
}

void GLMainWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
    else
        QWidget::keyPressEvent(e);
}



void GLMainWindow::on_persNearSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    if (changes)
         glWidget->setPerspective(  ui->persNearSpin->value(),
                                    ui->persFarSpin->value());

}

void GLMainWindow::on_persFarSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    if (changes)
         glWidget->setPerspective(
                                    ui->persNearSpin->value(),
                                    ui->persFarSpin->value());

}

void GLMainWindow::on_lookEyeXSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    if (changes)
        glWidget->setLookAt(QVector3D(ui->lookEyeXSpin->value(),
                                         ui->lookEyeYSpin->value(),
                                         ui->lookEyeZSpin->value()),
                               QVector3D(ui->lookCenterXSpin->value(),
                                         ui->lookCenterYSpin->value(),
                                         ui->lookCenterZSpin->value()),
                               QVector3D(ui->lookUpXSpin->value(),
                                         ui->lookUpYSpin->value(),
                                         ui->lookUpZSpin->value()));

}

void GLMainWindow::on_lookEyeYSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    if (changes)
        glWidget->setLookAt(QVector3D(ui->lookEyeXSpin->value(),
                                         ui->lookEyeYSpin->value(),
                                         ui->lookEyeZSpin->value()),
                               QVector3D(ui->lookCenterXSpin->value(),
                                         ui->lookCenterYSpin->value(),
                                         ui->lookCenterZSpin->value()),
                               QVector3D(ui->lookUpXSpin->value(),
                                         ui->lookUpYSpin->value(),
                                         ui->lookUpZSpin->value()));

}

void GLMainWindow::on_lookEyeZSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    if (changes)
        glWidget->setLookAt(QVector3D(ui->lookEyeXSpin->value(),
                                         ui->lookEyeYSpin->value(),
                                         ui->lookEyeZSpin->value()),
                               QVector3D(ui->lookCenterXSpin->value(),
                                         ui->lookCenterYSpin->value(),
                                         ui->lookCenterZSpin->value()),
                               QVector3D(ui->lookUpXSpin->value(),
                                         ui->lookUpYSpin->value(),
                                         ui->lookUpZSpin->value()));

}

void GLMainWindow::on_lookCenterXSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    if (changes)
        glWidget->setLookAt(QVector3D(ui->lookEyeXSpin->value(),
                                         ui->lookEyeYSpin->value(),
                                         ui->lookEyeZSpin->value()),
                               QVector3D(ui->lookCenterXSpin->value(),
                                         ui->lookCenterYSpin->value(),
                                         ui->lookCenterZSpin->value()),
                               QVector3D(ui->lookUpXSpin->value(),
                                         ui->lookUpYSpin->value(),
                                         ui->lookUpZSpin->value()));

}

void GLMainWindow::on_lookCenterYSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    if (changes)
        glWidget->setLookAt(QVector3D(ui->lookEyeXSpin->value(),
                                         ui->lookEyeYSpin->value(),
                                         ui->lookEyeZSpin->value()),
                               QVector3D(ui->lookCenterXSpin->value(),
                                         ui->lookCenterYSpin->value(),
                                         ui->lookCenterZSpin->value()),
                               QVector3D(ui->lookUpXSpin->value(),
                                         ui->lookUpYSpin->value(),
                                         ui->lookUpZSpin->value()));

}

void GLMainWindow::on_lookCenterZSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    if (changes)
        glWidget->setLookAt(QVector3D(ui->lookEyeXSpin->value(),
                                         ui->lookEyeYSpin->value(),
                                         ui->lookEyeZSpin->value()),
                               QVector3D(ui->lookCenterXSpin->value(),
                                         ui->lookCenterYSpin->value(),
                                         ui->lookCenterZSpin->value()),
                               QVector3D(ui->lookUpXSpin->value(),
                                         ui->lookUpYSpin->value(),
                                         ui->lookUpZSpin->value()));

}

void GLMainWindow::on_lookUpXSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    if (changes)
        glWidget->setLookAt(QVector3D(ui->lookEyeXSpin->value(),
                                         ui->lookEyeYSpin->value(),
                                         ui->lookEyeZSpin->value()),
                               QVector3D(ui->lookCenterXSpin->value(),
                                         ui->lookCenterYSpin->value(),
                                         ui->lookCenterZSpin->value()),
                               QVector3D(ui->lookUpXSpin->value(),
                                         ui->lookUpYSpin->value(),
                                         ui->lookUpZSpin->value()));

}

void GLMainWindow::on_lookUpYSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    if (changes)
        glWidget->setLookAt(QVector3D(ui->lookEyeXSpin->value(),
                                         ui->lookEyeYSpin->value(),
                                         ui->lookEyeZSpin->value()),
                               QVector3D(ui->lookCenterXSpin->value(),
                                         ui->lookCenterYSpin->value(),
                                         ui->lookCenterZSpin->value()),
                               QVector3D(ui->lookUpXSpin->value(),
                                         ui->lookUpYSpin->value(),
                                         ui->lookUpZSpin->value()));

}

void GLMainWindow::on_lookUpZSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    if (changes)
        glWidget->setLookAt(QVector3D(ui->lookEyeXSpin->value(),
                                         ui->lookEyeYSpin->value(),
                                         ui->lookEyeZSpin->value()),
                               QVector3D(ui->lookCenterXSpin->value(),
                                         ui->lookCenterYSpin->value(),
                                         ui->lookCenterZSpin->value()),
                               QVector3D(ui->lookUpXSpin->value(),
                                         ui->lookUpYSpin->value(),
                                         ui->lookUpZSpin->value()));

}

void GLMainWindow::on_action_exit_triggered()
{
    close();
}

void GLMainWindow::on_persNearSlider_valueChanged(int value)
{
    ui->persNearSpin->setValue(double(value) / 100.0);
}

void GLMainWindow::on_persFarSlider_valueChanged(int value)
{
    ui->persFarSpin->setValue(double(value) / 100.0);
}


/***********************************************/
/**************** POINT LIGHT UI ****************/
/***********************************************/

void GLMainWindow::on_pointLightPosXSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setPointLight();
}

void GLMainWindow::on_pointLightPosYSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setPointLight();
}

void GLMainWindow::on_pointLightPosZSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setPointLight();
}


void GLMainWindow::on_pointLightId1Spin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setPointLight();
}

void GLMainWindow::on_pointLightId2Spin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setPointLight();
}

void GLMainWindow::on_pointLightId3Spin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setPointLight();
}

void GLMainWindow::on_pointLightIa1Spin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setPointLight();
}

void GLMainWindow::on_pointLightIa2Spin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setPointLight();
}

void GLMainWindow::on_pointLightIa3Spin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setPointLight();
}

void GLMainWindow::on_pointLightIs1Spin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setPointLight();
}

void GLMainWindow::on_pointLightIs2Spin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setPointLight();
}

void GLMainWindow::on_pointLightIs3Spin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setPointLight();
}

void GLMainWindow::on_pointLightCoefA_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setPointLight();
}

void GLMainWindow::on_pointLightCoefB_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setPointLight();
}

void GLMainWindow::on_pointLightCoefC_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setPointLight();

}

void GLMainWindow::setPointLight(){
    glWidget->setPointLighting(QVector3D(ui->pointLightPosXSpin->value(),
                                           ui->pointLightPosYSpin->value(),
                                           ui->pointLightPosZSpin->value()),
                                 QVector3D(ui->pointLightIa1Spin->value(),
                                           ui->pointLightIa2Spin->value(),
                                           ui->pointLightIa3Spin->value()),
                                 QVector3D(ui->pointLightId1Spin->value(),
                                           ui->pointLightId2Spin->value(),
                                           ui->pointLightId3Spin->value()),
                                 QVector3D(ui->pointLightIs1Spin->value(),
                                           ui->pointLightIs2Spin->value(),
                                           ui->pointLightIs3Spin->value()),
                                 QVector3D(ui->pointLightCoefA->value(),
                                           ui->pointLightCoefB->value(),
                                            ui->pointLightCoefC->value())
                                 );
}

/***********************************************/
/***********************************************/
/***********************************************/


/***********************************************/
/**************** SPOT LIGHT UI ****************/
/***********************************************/

void GLMainWindow::on_spotLightPosXSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setSpotLight();
}

void GLMainWindow::on_spotLightPosYSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setSpotLight();
}

void GLMainWindow::on_spotLightPosZSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setSpotLight();
}


void GLMainWindow::on_spotLightId1Spin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setSpotLight();
}

void GLMainWindow::on_spotLightId2Spin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setSpotLight();
}

void GLMainWindow::on_spotLightId3Spin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setSpotLight();
}

void GLMainWindow::on_spotLightIa1Spin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setSpotLight();
}

void GLMainWindow::on_spotLightIa2Spin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setSpotLight();
}

void GLMainWindow::on_spotLightIa3Spin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setSpotLight();
}

void GLMainWindow::on_spotLightIs1Spin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setSpotLight();
}

void GLMainWindow::on_spotLightIs2Spin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setSpotLight();
}

void GLMainWindow::on_spotLightIs3Spin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setSpotLight();
}

void GLMainWindow::on_spotLightSpotDir1_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setSpotLight();
}

void GLMainWindow::on_spotLightSpotDir2_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setSpotLight();
}

void GLMainWindow::on_spotLightSpotDir3_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setSpotLight();

}

void GLMainWindow::on_spotLightCosCutoff_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setSpotLight();

}

void GLMainWindow::on_spotLightExponent_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setSpotLight();

}

void GLMainWindow::setSpotLight(){
    glWidget->setSpotLighting(QVector3D(ui->spotLightPosXSpin->value(),
                                           ui->spotLightPosYSpin->value(),
                                           ui->spotLightPosZSpin->value()),
                                 QVector3D(ui->spotLightIa1Spin->value(),
                                           ui->spotLightIa2Spin->value(),
                                           ui->spotLightIa3Spin->value()),
                                 QVector3D(ui->spotLightId1Spin->value(),
                                           ui->spotLightId2Spin->value(),
                                           ui->spotLightId3Spin->value()),
                                 QVector3D(ui->spotLightIs1Spin->value(),
                                           ui->spotLightIs2Spin->value(),
                                           ui->spotLightIs3Spin->value()),
                                 QVector3D(ui->spotLightSpotDir1->value(),
                                           ui->spotLightSpotDir2->value(),
                                            ui->spotLightSpotDir3->value()),
                                ui->spotLightCosCutoff->value(),
                                ui->spotLightExponent->value()
                                 );
}

/***********************************************/
/***********************************************/
/***********************************************/


/***********************************************/
/**************** DIRECTIONAL LIGHT UI ****************/
/***********************************************/

void GLMainWindow::on_dirLightDirXSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setDirLight();
}

void GLMainWindow::on_dirLightDirYSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setDirLight();
}

void GLMainWindow::on_dirLightDirZSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setDirLight();
}


void GLMainWindow::on_dirLightId1Spin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setDirLight();
}

void GLMainWindow::on_dirLightId2Spin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setDirLight();
}

void GLMainWindow::on_dirLightId3Spin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setDirLight();
}

void GLMainWindow::on_dirLightIa1Spin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setDirLight();
}

void GLMainWindow::on_dirLightIa2Spin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setDirLight();
}

void GLMainWindow::on_dirLightIa3Spin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setDirLight();
}

void GLMainWindow::on_dirLightIs1Spin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setDirLight();
}

void GLMainWindow::on_dirLightIs2Spin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setDirLight();
}

void GLMainWindow::on_dirLightIs3Spin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setDirLight();
}

void GLMainWindow::on_dirLightIntensity_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    setDirLight();
}


void GLMainWindow::setDirLight(){
    glWidget->setDirLighting(QVector3D(ui->dirLightDirXSpin->value(),
                                           ui->dirLightDirYSpin->value(),
                                           ui->dirLightDirZSpin->value()),
                                 QVector3D(ui->dirLightIa1Spin->value(),
                                           ui->dirLightIa2Spin->value(),
                                           ui->dirLightIa3Spin->value()),
                                 QVector3D(ui->dirLightId1Spin->value(),
                                           ui->dirLightId2Spin->value(),
                                           ui->dirLightId3Spin->value()),
                                 QVector3D(ui->dirLightIs1Spin->value(),
                                           ui->dirLightIs2Spin->value(),
                                           ui->dirLightIs3Spin->value()),
                                ui->dirLightIntensity->value()
                                 );
}

/***********************************************/
/***********************************************/
/***********************************************/


void GLMainWindow::setObsCamera(shared_ptr<GPUCamera> cam)
{
    changes = false;
    ui->lookEyeXSpin->setValue((float)cam->origin.x);
    ui->lookEyeYSpin->setValue((float)cam->origin.y);
    ui->lookEyeZSpin->setValue((float) cam->origin.z);

    ui->lookCenterXSpin->setValue(cam->vrp.x);
    ui->lookCenterYSpin->setValue(cam->vrp.y);
    ui->lookCenterZSpin->setValue(cam->vrp.z);

    ui->lookUpXSpin->setValue(cam->vUp.x);
    ui->lookUpYSpin->setValue(cam->vUp.y);
    ui->lookUpZSpin->setValue(cam->vUp.z);
    changes = true;
}

void GLMainWindow::setFrustumCamera(shared_ptr<GPUCamera> cam)
{
    changes = false;
    ui->persFarSpin->setValue(cam->dpost);
    ui->persNearSpin->setValue(cam->dant);

    ui->persFarSlider->setValue(cam->dpost*100);
    ui->persNearSlider->setValue(cam->dant*100);
    changes = true;

}
void GLMainWindow::refreshWindow() {
    auto visSetUp = Controller::getInstance()->getSetUp();

    // Pràctica 2 opcional: Carregar el setup des de menú i refresca el que calgui per
    // a reflectir-ho a la visualització
}


// Connexions de les opcions dels menús dels shaders i els advanced
void GLMainWindow::connectShaders()
{
    connect(ui->actionColor_Shader, SIGNAL(triggered()), glWidget, SLOT(activaColorShader()));
    connect(this->ui->action_depth, SIGNAL(triggered()), glWidget, SLOT(activaDepthShader()));
    connect(this->ui->actionNormal_Shader, SIGNAL(triggered()), glWidget, SLOT(activaNormalShader()));

    connect(this->ui->action_gouraud, SIGNAL(triggered()), glWidget, SLOT(activaGouraudShader()));
    connect(this->ui->action_phong, SIGNAL(triggered()), glWidget, SLOT(activaPhongShader()));
    connect(this->ui->actionGouraud_Blinn_Phong_Shader, SIGNAL(triggered()), glWidget, SLOT(activaGouraudBlinnShader()));
    connect(this->ui->actionBlinn_Phong_Shader, SIGNAL(triggered()), glWidget, SLOT(activaBlinnPhongShader()));
    connect(this->ui->action_toon, SIGNAL(triggered()), glWidget, SLOT(activaToonShader()));

    connect(this->ui->action_environmental_mapping, SIGNAL(triggered()), glWidget, SLOT(activaEnvMapping()));
    connect(this->ui->action_reflections, SIGNAL(triggered()), glWidget, SLOT(activaReflection()));
    connect(this->ui->action_transparencies, SIGNAL(triggered()), glWidget, SLOT(activaTransparency()));
    connect(this->ui->actionCentered_Target, SIGNAL(triggered()), glWidget, SLOT(activaNightVision()));

    connect(this->ui->actionHighlight_Region, SIGNAL(triggered()), glWidget, SLOT(activaTempestaFortnite()));

}


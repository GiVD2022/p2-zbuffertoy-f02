#include "ViewGL/GLWidget.hh"


GLWidget::GLWidget(QWidget *parent) : QGLWidget(QGLFormat(QGL::SampleBuffers), parent) {

    setFocusPolicy( Qt::StrongFocus );

}

GLWidget::GLWidget(const QGLFormat &glf, QWidget *parent) : QGLWidget(glf, parent) {

    setFocusPolicy( Qt::StrongFocus );
    auto cameraGPU = make_shared<GPUCamera>(this->size().width(), this->size().height());
    Controller::getInstance()->getSetUp()->setCamera(cameraGPU);
}


GLWidget::~GLWidget() {

}


/* Interacció amb GL i inicialització dels programes a la GPU */

/**
 * @brief GLWidget::initializeGL()
 */
void GLWidget::initializeGL() {

    glClearColor(0.0, 0.0, 0.0, 1.0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_RGBA);
    glEnable(GL_DOUBLE);
    glEnable(GL_TEXTURE_2D);

    initShadersGPU();
    Controller::getInstance()->getSetUp()->setAmbientGlobalToGPU(program);

    // Creacio d'una Light per a poder modificar el seus valors amb la interficie
    // TO DO: Pràctica 2: Fase 1:  Canviar per a que siguin GPULigths i usar la factory GPULightFactory que facis nova

    //Creacio de tres llums per defecte per a poder interactuar des de la ui
    // Default point light
    vec3 position1 = vec3(-25,25,25);
    vec3 Ia1 = vec3(0.3,0.3,0.3);
    vec3 Id1 = vec3(1,1,1);
    vec3 Is1 = vec3(0.5,0.5,0.5);
    float a1 = 0.0;
    float b1 = 0.0;
    float c1 = 1.0;
    auto light1 = GPULightFactory::getInstance().createLight(position1, Ia1, Id1, Is1, a1, b1, c1, LightFactory::POINTLIGHT);
    Controller::getInstance()->getSetUp()->addLight(light1);

    /*
    // Default directional light
    vec3 direction2 = vec3(1.0, 0.0, 0.0);
    vec3 Ia2 = vec3(0.1, 0.1, 0.1);
    vec3 Id2 = vec3(1.0, 0.5, 0.0);
    vec3 Is2 = vec3(1.0, 0.5, 0.0);
    float intensity2 = 1.0;
    auto light2 = GPULightFactory::getInstance().createLight(direction2, Ia2, Id2, Is2, intensity2, LightFactory::DIRECTIONALLIGHT);
    Controller::getInstance()->getSetUp()->addLight(light2);

    // Default spot light
    vec3 position3 = vec3(0.0, 2.0, 0.0);
    vec3 Ia3 = vec3(0.1, 0.1, 0.1);
    vec3 Id3 = vec3(0.0, 0.5, 1.0);
    vec3 Is3 = vec3(1.0, 0.0, 0.5);
    vec3 spotDirection3 = vec3(0,-1,0);
    float spotCosineCutoff3 = 1.2;
    float spotExponent3 = 1;
    auto light3 = GPULightFactory::getInstance().createLight(position3, Ia3, Id3, Is3, spotDirection3, spotCosineCutoff3, spotExponent3, LightFactory::SPOTLIGHT);
    Controller::getInstance()->getSetUp()->addLight(light3);
    */
    //send them to the gpu
    Controller::getInstance()->getSetUp()->lightsToGPU(program);

    shared_ptr<GPUCamera> camera = Controller::getInstance()->getSetUp()->getCamera();
    auto scene = Controller::getInstance()->getScene();

    camera->init(this->size().width(), this->size().height(), scene->capsaMinima);
    emit ObsCameraChanged(camera);
    emit FrustumCameraChanged(camera);

    glViewport(camera->vp.pmin[0], camera->vp.pmin[1], camera->vp.a, camera->vp.h);

}

/**
 * @brief GLWidget::paintGL()
 */
void GLWidget::paintGL() {

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    shared_ptr<GPUCamera> camera = Controller::getInstance()->getSetUp()->getCamera();
    auto scene = Controller::getInstance()->getScene();

    Controller::getInstance()->getSetUp()->lightsToGPU(program);
    camera->toGPU(program);
    scene->draw();

}

/**
 * @brief GLWidget::resizeGL()
 */
void GLWidget::resizeGL(int width, int height) {


    shared_ptr<GPUCamera> camera = Controller::getInstance()->getSetUp()->getCamera();

    camera->vp.a = width;
    camera->vp.h = height;
    auto scene = Controller::getInstance()->getScene();
    camera->CalculaWindow(scene->capsaMinima);
    glViewport(camera->vp.pmin[0], camera->vp.pmin[1], camera->vp.a, camera->vp.h);
    emit FrustumCameraChanged(camera);
    updateGL();
}

/**
 * @brief GLWidget::initShadersGPU
 */
void GLWidget::initShadersGPU(){
    GLShader *glshader = new GLShader("://resources/GPUshaders/vshader1.glsl", "://resources/GPUshaders/fshader1.glsl", program);
    if (glshader != nullptr) {
        program->link();
        program->bind();
    }
}

QSize GLWidget::minimumSizeHint() const {
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const {
    return QSize(400, 400);
}

/** Gestio de les animacions i la gravació d'imatges ***/

void GLWidget::setCurrentFrame(){

    auto scene = Controller::getInstance()->getScene();
    scene->update(currentFrame);
    updateGL();
    this->saveFrame();
    currentFrame++;

    if (currentFrame == MAXFRAMES)
        timer->stop();

}

void GLWidget::saveFrame(){
    this->grabFrameBuffer().save("screen_output_"+QVariant(currentFrame).toString()+".jpg");
}

void GLWidget::saveImage(){
    this->grabFrameBuffer().save("screen_output_"+QVariant(currentImage).toString()+".jpg");
    currentImage++;
}



/** Metodes SLOTS que serveixen al builder per a actualitzar l'escena i els objectes */
void GLWidget::updateObject(shared_ptr<GPUMesh> obj) {

    obj->toGPU(program);
    updateGL();
}

void GLWidget::updateScene() {
    // Control de la nova escena a la GPU
    auto sc = Controller::getInstance()->getScene();
    sc->toGPU(program);
    Controller::getInstance()->setScene(sc);
    // Podeu utilitzar l'altre constructor de Camera per inicialitzar els
    // parametres de la camera.
    auto camera = make_shared<GPUCamera>(this->size().width(), this->size().height());
    Controller::getInstance()->getSetUp()->setCamera(camera);

    camera->actualitzaCamera(sc->capsaMinima);

    emit ObsCameraChanged(camera);
    emit FrustumCameraChanged(camera);

    updateGL();

}

/** Metodes que es criden des dels menús */

void GLWidget::saveAnimation() {
    // Comença el timer de l'animació
    timer = new QTimer(this);
    currentFrame=0;
    currentImage=0;
    connect(timer, SIGNAL(timeout()), this, SLOT(setCurrentFrame()));
    timer->start(1000);

}

void GLWidget::activaColorShader() {
    //TO DO: Pràctica 2: A implementar a la fase 1
    GLShader *glshader = new GLShader("://resources/GPUshaders/vshader_color.glsl", "://resources/GPUshaders/fshader_color.glsl", program);
    if (glshader != nullptr) {
        program->link();
        program->bind();
    }
    auto sc = Controller::getInstance()->getScene();
    sc->toGPU(program);
    updateGL();
    qDebug()<<"Estic a Color Shader";
}

void GLWidget::activaDepthShader() {
    //TO DO: Pràctica 2: A implementar a la fase 1
    GLShader *glshader = new GLShader("://resources/GPUshaders/vshader_depth.glsl", "://resources/GPUshaders/fshader_depth.glsl", program);
    if (glshader != nullptr) {
        program->link();
        program->bind();
    }
    auto sc = Controller::getInstance()->getScene();
    sc->toGPU(program);
    updateGL();
    qDebug()<<"Estic a Depth Shader";
}

void GLWidget::activaNormalShader() {
    //TO DO: Pràctica 2: A implementar a la fase 1

    GLShader *glshader = new GLShader("://resources/GPUshaders/vshader_normal.glsl", "://resources/GPUshaders/fshader_normal.glsl", program);
    if (glshader != nullptr) {
        program->link();
        program->bind();
    }
    auto sc = Controller::getInstance()->getScene();
    sc->toGPU(program);
    updateGL();
    qDebug()<<"Estic a Normal Shader";
}

void GLWidget::activaGouraudShader() {
    //TO DO: Pràctica 2:  implementar a la fase 1
    GLShader *glshader = new GLShader("://resources/GPUshaders/vshader_gouraud_phong.glsl", "://resources/GPUshaders/fshader_gouraud.glsl", program);
    if (glshader != nullptr) {
        program->link();
        program->bind();
    }
    auto sc = Controller::getInstance()->getScene();
    sc->toGPU(program);
    updateGL();
    qDebug()<<"Estic a Gouraud - Phong shader";

}
void GLWidget::activaPhongShader() {
    //TO DO: Pràctica 2:  implementar a la fase 1
    GLShader *glshader = new GLShader("://resources/GPUshaders/vshader_phong_phong.glsl", "://resources/GPUshaders/fshader_phong_phong.glsl", program);
    if (glshader != nullptr) {
        program->link();
        program->bind();
    }
    auto sc = Controller::getInstance()->getScene();
    sc->toGPU(program);
    updateGL();
    qDebug()<<"Estic a Phong - Phong Shader";

}

void GLWidget::activaGouraudBlinnShader() {
    //TO DO: Pràctica 2:  implementar a la fase 1
    GLShader *glshader = new GLShader("://resources/GPUshaders/vshader_gouraud_blinn_phong.glsl", "://resources/GPUshaders/fshader_gouraud.glsl", program);
    if (glshader != nullptr) {
        program->link();
        program->bind();
    }
    auto sc = Controller::getInstance()->getScene();
    sc->toGPU(program);
    updateGL();
    qDebug()<<"Estic a Gouraud - Blinn-Phong shader";

}
void GLWidget::activaBlinnPhongShader() {
    //TO DO: Pràctica 2:  implementar a la fase 1
    GLShader *glshader = new GLShader("://resources/GPUshaders/vshader_phong_blinnphong.glsl", "://resources/GPUshaders/fshader_phong_blinnphong.glsl", program);
    if (glshader != nullptr) {
        program->link();
        program->bind();
    }
    auto sc = Controller::getInstance()->getScene();
    sc->toGPU(program);
    updateGL();
    qDebug()<<"Estic a Phong - Blinn-Phong Shader";

}

void GLWidget::activaTempestaFortnite() {
    //TO DO: Pràctica 2:  implementar a la fase 1
    GLShader *glshader = new GLShader("://resources/GPUshaders/vshader_blue_gouraud_blinn_phong.glsl", "://resources/GPUshaders/fshader_blue_gouraud.glsl", program);
    if (glshader != nullptr) {
        program->link();
        program->bind();
    }
    auto sc = Controller::getInstance()->getScene();
    sc->toGPU(program);
    updateGL();
    qDebug()<<"Estic a Fortnite Shader";

}


void GLWidget::activaToonShader() {
    //TO DO: Pràctica 2:  implementar a la fase 1
    qDebug()<<"Estic a Toon";
}


void GLWidget::activaReflection() {
   //TO DO: Pràctica 2:  implementar a la fase 2
     qDebug()<<"Estic a Reflection";
}

void GLWidget::activaEnvMapping() {
    //TO DO: Pràctica 2:  implementar a la fase 2
    qDebug()<<"Estic a Environmental Mapping";
}

void GLWidget::activaTransparency() {
    //TO DO: Pràctica 2:  implementar a la fase 2
    qDebug()<<"Estic a Transparencia";
}



void GLWidget::setPerspective(float nearPlane, float farPlane)
{
    shared_ptr<GPUCamera> camera = Controller::getInstance()->getSetUp()->getCamera();

    camera->setFrustum(camera->vfovRadians DEGREES, nearPlane, farPlane, TipProj::PERSPECTIVA);

    updateGL();
}

void GLWidget::setLookAt(const QVector3D &eye, const QVector3D &center, const QVector3D& up)
{
    vec4 lookfrom(eye[0], eye[1], eye[2], 1.0);
    vec4 lookat(center[0], center[1], center[2], 1.0);
    vec4 vup(up[0], up[1], up[2], 1.0);

    shared_ptr<GPUCamera> camera = Controller::getInstance()->getSetUp()->getCamera();

    camera->setObservador(lookfrom, lookat, vup);

    updateGL();
}

void GLWidget::setPointLighting(const QVector3D &lightPos, const QVector3D &Ia, const QVector3D &Id,
                           const QVector3D &Is, const QVector3D &coefs)
{
    vec3 position = vec3(lightPos[0],lightPos[1], lightPos[2]);
    vec3 intensityA = vec3(Ia[0], Ia[1], Ia[2]);
    vec3 intensityD = vec3(Id[0], Id[1], Id[2]);
    vec3 intensityS = vec3(Is[0], Is[1], Is[2]);
    vec3 coeficients = vec3(coefs[0], coefs[1], coefs[2]);
    auto lights = Controller::getInstance()->getSetUp()->getLights();
    if (auto point_light = dynamic_cast<PointLight*>(lights[0].get())) {
        point_light->setIa(intensityA);
        point_light->setId(intensityD);
        point_light->setIs(intensityS);
        point_light->setPosition(position);
        point_light->setCoeficients(coeficients);
        Controller::getInstance()->getSetUp()->setLightIndex(lights[0], 0);
        Controller::getInstance()->getSetUp()->lightsToGPU(program);
    } else{
        qDebug()<<"First light is not a PointLight!";
        qDebug()<<"Couldn't load the point light from the ui";
    }
    updateGL();
}

void GLWidget::setDirLighting(const QVector3D &lightDir, const QVector3D &Ia, const QVector3D &Id,
                           const QVector3D &Is, const float dirInt)
{
    vec3 lightDirection = vec3(lightDir[0],lightDir[1], lightDir[2]);
    vec3 intensityA = vec3(Ia[0], Ia[1], Ia[2]);
    vec3 intensityD = vec3(Id[0], Id[1], Id[2]);
    vec3 intensityS = vec3(Is[0], Is[1], Is[2]);
    auto lights = Controller::getInstance()->getSetUp()->getLights();
    if (auto dir_light = dynamic_cast<DirectionalLight*>(lights[1].get())) {
        dir_light->setIa(intensityA);
        dir_light->setId(intensityD);
        dir_light->setIs(intensityS);
        dir_light->setDirection(lightDirection);
        dir_light->setIntensity(dirInt);
        Controller::getInstance()->getSetUp()->setLightIndex(lights[1], 1);
        Controller::getInstance()->getSetUp()->lightsToGPU(program);
    } else{
        qDebug()<<"First light is not a DirectionalLight!";
        qDebug()<<"Couldn't load the directional light from the ui";
    }
    updateGL();
}

void GLWidget::setSpotLighting(const QVector3D &lightPos, const QVector3D &Ia, const QVector3D &Id,
                           const QVector3D &Is, const QVector3D &spotDir, const float spotCosCutoff, const float spotExp)
{
    vec3 position = vec3(lightPos[0],lightPos[1], lightPos[2]);
    vec3 intensityA = vec3(Ia[0], Ia[1], Ia[2]);
    vec3 intensityD = vec3(Id[0], Id[1], Id[2]);
    vec3 intensityS = vec3(Is[0], Is[1], Is[2]);
    vec3 spotDirection = vec3(spotDir[0], spotDir[1], spotDir[2]);
    auto lights = Controller::getInstance()->getSetUp()->getLights();
    if (auto spot_light = dynamic_cast<SpotLight*>(lights[2].get())) {
        spot_light->setIa(intensityA);
        spot_light->setId(intensityD);
        spot_light->setIs(intensityS);
        spot_light->setPosition(position);
        spot_light->setSpotDirection(spotDirection);
        spot_light->setSpotCosineCutoff(spotCosCutoff);
        spot_light->setSpotExponent(spotExp);
        Controller::getInstance()->getSetUp()->setLightIndex(lights[2], 2);
        Controller::getInstance()->getSetUp()->lightsToGPU(program);
    } else{
        qDebug()<<"First light is not a SpotLight!";
        qDebug()<<"Couldn't load the spot light from the ui";
    }
    updateGL();
}




/**  Mètodes d'interacció amb el ratolí */

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton)
    {
        if(lastPos.y()!= event->y() && lastPos.x()!= event->x()) {
           setXRotation(dy);
           setYRotation(dx);
        } else if(lastPos.y()!= event->y()) {// rotar la camera
            setXRotation(dy);
        } else if (lastPos.x()!= event->x()) {
            setYRotation(dx);
        }

    } else if (event->buttons() & Qt::RightButton) {
       // Zoom: canviar la mida de la window
        if(lastPos.y()> event->y())
             Zoom(-1);
        else
             Zoom(1);
    }

    lastPos = event->pos();
}


void GLWidget::setXRotation(int angle)
{
    shared_ptr<GPUCamera> camera = Controller::getInstance()->getSetUp()->getCamera();

    if (angle >0) {
        camera->angX += 5;
    } else if (angle<0)
        camera->angX -= 5;
    qNormalizeAngle(camera->angX);

    camera->rotaCamera();

    emit ObsCameraChanged(camera);

    updateGL();
}

void GLWidget::setYRotation(int angle)
{
    shared_ptr<GPUCamera> camera = Controller::getInstance()->getSetUp()->getCamera();

    if (angle >0) {
        camera->angY += 5;
    } else if (angle<0)
        camera->angY-= 5;
    qNormalizeAngle(camera->angY);

    camera->rotaCamera();

    emit ObsCameraChanged(camera);

    updateGL();
}

void GLWidget::qNormalizeAngle(double &angle)
{
    while (angle < 0)
        angle += 360*16;
    while (angle > 360)
        angle -= 360*16;
}

void GLWidget::Zoom (int positiu) {

    shared_ptr<GPUCamera> camera = Controller::getInstance()->getSetUp()->getCamera();

    camera->AmpliaWindow(positiu*(0.005));

    emit FrustumCameraChanged(camera);

    updateGL();
}


#include "GPUSetUp.hh"

GPUSetUp::GPUSetUp()
{
  camera = make_shared<GPUCamera>(500, 500);
  this->setGlobalLight(vec3(1.0, 0.0, 0.0));
}


shared_ptr<GPUCamera> GPUSetUp::getCamera() {
    return(camera);
}


vec3 GPUSetUp::getGlobalLight() {
    return globalLight;
}

std::vector<shared_ptr<GPULight>> GPUSetUp::getLights() {
    return lights;
}



void GPUSetUp::setCamera(shared_ptr<GPUCamera> cam) {
    this->camera = cam;
}

void GPUSetUp::setGlobalLight(vec3 globalLight) {
    this->globalLight = globalLight;
}
void GPUSetUp::setLights(std::vector<shared_ptr<GPULight>> lights) {
    this->lights = lights;
}

/**
 * @brief GPUSetUp::getLightActual
 * @return
 */
shared_ptr<GPULight> GPUSetUp::getLightActual() {
    // TO DO OPCIONAL: A modificar si es vol canviar el comportament de la GUI
    // Ara per ara dona com a Light actual la darrera que s'ha inserit
    return (lights[lights.size()-1]);
}

/**
 * @brief GPUSetUp::setLightActual
 * @param shared_ptr<Light> l
 */
void GPUSetUp::setLightActual(shared_ptr<GPULight> l){
    lights[lights.size()-1]=l;
}

/**
 * @brief GPUSetUp::addLight
 * @param shared_ptr<Light> l
 */
void GPUSetUp::addLight(shared_ptr<GPULight> l) {
    lights.push_back(l);
}



/**
 * @brief Scene::setAmbientToGPU
 * @param program
 */
void GPUSetUp::setAmbientGlobalToGPU(shared_ptr<QGLShaderProgram> program){
    // Pràctica 2: TO DO: A implementar a la fase 1
    GLuint idAmbientGlobal;
    idAmbientGlobal = program->uniformLocation("ambientGlobal");
    glUniform3fv(idAmbientGlobal, 1, globalLight);
    //des d'on crido al toGPU? Comú a tots els objectes ->initializeGL

}

/**
 * @brief GPUSetUp::lightsToGPU
 * @param program
 */
void GPUSetUp::lightsToGPU(shared_ptr<QGLShaderProgram> program){
    // Practica 2: TO DO: A implementar a la fase 1
    // Declare a vector of gl_IdLight structures
    qDebug() << "reading lights, num:.....";
    int numLights = static_cast<int>(lights.size());
    qDebug() << numLights;
    struct gl_IdLight {
        GLuint Ia;
        GLuint Id;
        GLuint Is;
        GLuint position;
        GLuint coeficients;

        // Directional lights
        GLuint direction;
        GLuint intensity;
    };
    gl_IdLight gl_IdLights[5];

    // Get the uniform locations for each of the properties for all 5 lights
    for (int i = 0; i < numLights; i++) {
        gl_IdLights[i].Ia = program->uniformLocation(QString("light_info[%1].Ia").arg(i));
        gl_IdLights[i].Id = program->uniformLocation(QString("light_info[%1].Id").arg(i));
        gl_IdLights[i].Is = program->uniformLocation(QString("light_info[%1].Is").arg(i));
        gl_IdLights[i].position = program->uniformLocation(QString("light_info[%1].position").arg(i));
        gl_IdLights[i].coeficients = program->uniformLocation(QString("light_info[%1].coeficients").arg(i));

        // Directional lights
        gl_IdLights[i].direction = program->uniformLocation(QString("light_info[%1].direction").arg(i));
        gl_IdLights[i].intensity = program->uniformLocation(QString("light_info[%1].intensity").arg(i));
    }

    // Bind the values of each property for all 5 lights
    for (int i = 0; i < numLights; i++) {
        if (auto point_light = dynamic_cast<PointLight*>(lights[i].get())) {
            glUniform3fv(gl_IdLights[i].Ia, 1, point_light->getIa());
            glUniform3fv(gl_IdLights[i].Id, 1, point_light->getId());
            glUniform3fv(gl_IdLights[i].Is, 1, point_light->getIs());
            glUniform4fv(gl_IdLights[i].position, 1, point_light->getPosition());
            glUniform3fv(gl_IdLights[i].coeficients, 1, point_light->getCoeficients());
            qDebug() << "point lights.....";
        } else if (auto directional_light = dynamic_cast<DirectionalLight*>(lights[i].get())) {
            glUniform3fv(gl_IdLights[i].Ia, 1, directional_light->getIa());
            glUniform3fv(gl_IdLights[i].Id, 1, directional_light->getId());
            glUniform3fv(gl_IdLights[i].Is, 1, directional_light->getIs());
            glUniform4fv(gl_IdLights[i].direction, 1, directional_light->getDirection());
            glUniform1f(gl_IdLights[i].intensity, directional_light->getIntensity());
            qDebug() << "directional lights.....";
        }else {
            // Handle other types of lights, e.g. directional light, here
        }
    }


}

// TODO (opcional) si es llegeix el setUp de fitxer cal alctualitzar aquest codi per
// a crear les llums de tipus GPU
void GPUSetUp::read(const QJsonObject &json)
{
    if (json.contains("camera")) {
        QJsonObject camObject = json["camera"].toObject();
        camera->read(camObject);
    }
    if (json.contains("lights") && json["lights"].isArray()) {
        QJsonArray lightsArray = json["lights"].toArray();

        for (int lightIndex = 0; lightIndex < lightsArray.size(); lightIndex++) {
            QJsonObject lightObject = lightsArray[lightIndex].toObject();
            shared_ptr<GPULight> l;
            if (lightObject.contains("type") && lightObject["type"].isString()) {
                QString ligthStr = lightObject["type"].toString().toUpper();
                l = GPULightFactory::getInstance().createLight(LightFactory::getInstance().getLightType(ligthStr));
                l->read(lightObject);
                lights.push_back(l);
            }
        }
    }
    if (json.contains("globalLight") && json["globalLight"].isArray()) {
        QJsonArray globalVec = json["globalLight"].toArray();
        globalLight[0] = globalVec[0].toDouble();
        globalLight[1] = globalVec[1].toDouble();
        globalLight[2] = globalVec[2].toDouble();
    }

}
//! [0]

void GPUSetUp::write(QJsonObject &json) const
{
    QJsonObject cameraObject;
    camera->write(cameraObject);
    json["camera"] = cameraObject;

    QJsonArray lightsArray;
    for (const shared_ptr<GPULight> &l : lights) {
        QJsonObject lightObject;
        auto  value = LightFactory::getInstance().getIndexType (l);
        QString className = LightFactory::getInstance().getNameType(value);

        l->write(lightObject);
        lightObject["type"] = className;
        lightsArray.append(lightObject);
    }
    json["lights"] = lightsArray;

    QJsonArray auxArray;
    auxArray.append(globalLight[0]);auxArray.append(globalLight[1]);auxArray.append(globalLight[2]);
    json["globalLight"] = auxArray;

}

void GPUSetUp::print(int indentation) const
{
    const QString indent(indentation * 2, ' ');

    camera->print(2);
    QTextStream(stdout) << indent << "Ligths:\t\n";
    for (unsigned int i =0; i< lights.size(); i++) {
        auto value = LightFactory::getInstance().getIndexType (lights[i]);
        QString className = LightFactory::getInstance().getNameType(value);
        QTextStream(stdout) << indent+2 << "type:\t" << className << "\n";

        lights[i]->print(2);

    }
    QTextStream(stdout) << indent << "globalLight:\t" << globalLight[0] << ", "<< globalLight[1] << ", "<< globalLight[2] << "\n";
}


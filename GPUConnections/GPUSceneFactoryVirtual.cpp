#include "GPUSceneFactoryVirtual.hh"


shared_ptr<GPUScene>  GPUSceneFactoryVirtual::createScene() {
    scene= make_shared<GPUScene>();
    return scene;
}

shared_ptr<GPUScene> GPUSceneFactoryVirtual::createScene(QString filename) {

    scene= make_shared<GPUScene>();
    load(filename);
    print(0);

    return scene;
}

//! [3]
bool GPUSceneFactoryVirtual::load(QString nameFile)
{
    QFile loadFile(nameFile);
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open the virtual scene file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();
    QJsonParseError error;
    QJsonDocument loadDoc( QJsonDocument::fromJson(saveData, &error));


    if (loadDoc.isNull()) {
        qWarning("Parse error in json virtual scene file.");
        return false;
    }
    QJsonObject object = loadDoc.object();
    read(object);

    QTextStream(stdout) << "Loaded virtual scene using " << "...\n";
    return true;
}
//! [3]

//! [4]
bool GPUSceneFactoryVirtual::save(QString nameFile) const
{
    QFile saveFile(QString(nameFile.append(".json")));

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open virtual scene file.");
        return false;
    }

    QJsonObject setUpObject;
    write(setUpObject);
    saveFile.write(QJsonDocument(setUpObject).toJson());

    return true;
}


void GPUSceneFactoryVirtual::read(const QJsonObject &json)
{
    if (json.contains("scene") && json["scene"].isString())
        scene->name = json["scene"].toString();
    if (json.contains("typeScene") && json["typeScene"].isString())
        currentType = getSceneFactoryType(json["typeScene"].toString());

    if (json.contains("objects") && json["objects"].isArray()) {
        QJsonArray objectsArray = json["objects"].toArray();

        for (int objectIndex = 0; objectIndex < objectsArray.size(); objectIndex++) {
            QJsonObject objectObject = objectsArray[objectIndex].toObject();
            shared_ptr<GPUObject> o;
            if (objectObject.contains("type") && objectObject["type"].isString()) {
                QString objStr = objectObject["type"].toString().toUpper();
                o = dynamic_pointer_cast<GPUObject>(
                            GPUObjectFactory::getInstance().createObject(ObjectFactory::getInstance().getObjectType(objStr)));

                QTextStream(stdout) << "Readig a GPUscene factory" <<"\n";

                //read animation for each object
                if (objectObject.contains("animations") && objectObject["animations"].isArray()) {
                    QJsonArray animArray = objectObject["animations"].toArray();
                    for (int animIndex = 0; animIndex < animArray.size(); animIndex++) {
                        QJsonObject animObject = animArray[animIndex].toObject();
                        shared_ptr<Animation> anim = make_shared<Animation>();
                        if (animObject.contains("frameIni") && animObject["frameIni"].isDouble()){
                            anim->frameIni = animObject["frameIni"].toInt();
                        }
                        if (animObject.contains("frameFinal") && animObject["frameFinal"].isDouble()){
                            anim->frameFinal = animObject["frameFinal"].toInt();
                        }
                        if (animObject.contains("translation") && animObject["translation"].isArray()) {
                            QJsonArray translationArray = animObject["translation"].toArray();
                            shared_ptr<TG> tg = make_shared<TranslateTG>(vec3(translationArray[0].toDouble(), translationArray[1].toDouble(), translationArray[2].toDouble()));
                            anim->transf = tg;
                            o->translation = true;
                        }
                        else if (animObject.contains("scale") && animObject["scale"].isArray()) {
                            QJsonArray scaleArray = animObject["scale"].toArray();
                            shared_ptr<TG> tg = make_shared<ScaleTG>(vec3(scaleArray[0].toDouble(), scaleArray[1].toDouble(), scaleArray[2].toDouble()));
                            anim->transf = tg;
                            o->scale = true;
                        }

                        o->addAnimation(anim);
                    }
                }

                o->read(objectObject);

                // Afegir objecte a l'escena virtual ja amb el seu material corresponent
				scene->addObject(o);
            }
        }
    }

}
//! [0]
void GPUSceneFactoryVirtual:: write(QJsonObject &json) const
{
   json["scene"] = scene->name;
   json["typeScene"] = GPUSceneFactory::getNameType(currentType);


    QJsonArray objectsArray;
    for (const shared_ptr<Object> o : scene->objects) {
        QJsonObject objectObject;
        int  value = ObjectFactory::getInstance().getIndexType (o);
        QString className = ObjectFactory::getInstance().getNameType(value);

        o->write(objectObject);
        objectObject["type"] = className;
        objectsArray.append(objectObject);
    }
    json["objects"] = objectsArray;
}

void GPUSceneFactoryVirtual::print(int indentation) const
{
    const QString indent(indentation * 2, ' ');
    QTextStream(stdout) << indent << "scene:\t" << scene->name << "\n";
    QTextStream(stdout) << indent << "typeScene:\t" << getNameType(currentType) << "\n";

    QTextStream(stdout) << indent << "Objects:\t\n";
    for (unsigned int i =0; i< scene->objects.size(); i++) {
        auto value = ObjectFactory::getInstance().getIndexType (scene->objects[i]);
        QString className = ObjectFactory::getInstance().getNameType(value);
        QTextStream(stdout) << indent+2 << "name:\t" << scene->objects[i]->name <<"\n";
        QTextStream(stdout) << indent+2 << "type:\t" << className << "\n";
        scene->objects[i]->print(2);
    }
 }

#include "SetUp.hh"

SetUp::SetUp()
{
  shade = make_shared<ShadingStrategy>();
  MAXDEPTH = 1;
  numSamples = 1;
  background = true;
  downBackground = vec3(1.0, 1.0, 1.0);
  topBackground = vec3(0.5, 0.7, 1.0);

}

bool SetUp::load( QString nameFile)
{
    QFile loadFile(nameFile);
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open the setup file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonParseError error;
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData, &error));


    if (loadDoc.isNull()) {
        qWarning("Parse error in json.");
        return false;
    }
    QJsonObject object = loadDoc.object();
    read(object);

    QTextStream(stdout) << "Loaded setup using "<< "...\n";
    return true;
}
//! [3]

//! [4]
bool SetUp::save( QString nameFile) const
{
    QFile saveFile(QString(nameFile.append(".json")));

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open setup file.");
        return false;
    }

    QJsonObject setUpObject;
    write(setUpObject);
    saveFile.write(QJsonDocument(setUpObject).toJson());

    return true;
}

//! [0]
void SetUp::read(const QJsonObject &json)
{
    if (json.contains("background") && json["background"].isBool())
        background = json["background"].toBool();
    if (json.contains("colorTopBackground") && json["colorTopBackground"].isArray()) {
        QJsonArray globalVec = json["colorTopBackground"].toArray();
        topBackground[0] = globalVec[0].toDouble();
        topBackground[1] = globalVec[1].toDouble();
        topBackground[2] = globalVec[2].toDouble();
    }
    if (json.contains("colorDownBackground") && json["colorDownBackground"].isArray()) {
        QJsonArray globalVec = json["colorDownBackground"].toArray();
        downBackground[0] = globalVec[0].toDouble();
        downBackground[1] = globalVec[1].toDouble();
        downBackground[2] = globalVec[2].toDouble();
    }
    if (json.contains("MAXDEPTH") && json["MAXDEPTH"].isDouble())
        MAXDEPTH = json["MAXDEPTH"].toInt();

    if (json.contains("numSamples") && json["numSamples"].isDouble())
        numSamples = json["numSamples"].toInt();

    if (json.contains("shading") && json["shading"].isString()) {
        QString tipus = json["shading"].toString().toUpper();
        ShadingFactory::SHADING_TYPES t = ShadingFactory::getInstance().getShadingType(tipus);
        shade = ShadingFactory::getInstance().createShading(t);
    }
}
//! [0]

void SetUp::write(QJsonObject &json) const
{

    QJsonArray auxArray0;
    auxArray0.append(topBackground[0]);auxArray0.append(topBackground[1]);auxArray0.append(topBackground[2]);
    json["colorTopBackground"] = auxArray0;

    QJsonArray auxArray1;
    auxArray1.append(downBackground[0]);auxArray1.append(downBackground[1]);auxArray1.append(downBackground[2]);
    json["colorDownBackground"] = auxArray1;

    json["background"] = background;
    json["MAXDEPTH"] = MAXDEPTH;
    json["numSamples"] = numSamples;

    auto  value = ShadingFactory::getInstance().getIndexType (shade);
    QString className = ShadingFactory::getInstance().getNameType(value);
    json["shading"] = className;

}

void SetUp::print(int indentation) const
{
    const QString indent(indentation * 2, ' ');

    QTextStream(stdout) << indent << "background:\t" << background << "\n";
    QTextStream(stdout) << indent << "MAXDEPTH:\t" << MAXDEPTH << "\n";
    QTextStream(stdout) << indent << "numSamples:\t" << numSamples << "\n";
    QTextStream(stdout) << indent << "colorTopBackground:\t" << topBackground[0] << ", "<< topBackground[1] << ", "<< topBackground[2] << "\n";
    QTextStream(stdout) << indent << "colorDownBackground:\t" << downBackground[0] << ", "<< downBackground[1] << ", "<< downBackground[2] << "\n";

    auto  value = ShadingFactory::getInstance().getIndexType (shade);
    QString className = ShadingFactory::getInstance().getNameType(value);
    QTextStream(stdout) << indent << "shading type:\t" << className << "\n";
}


QString SetUp::getOutputFile() {
    return outputFile;
}


bool SetUp::getBackground() {
    return background;
}

vec3 SetUp::getTopBackground(){ return topBackground; }
vec3 SetUp::getDownBackground() {return downBackground; }

int SetUp::getMAXDEPTH() { return MAXDEPTH;}

int SetUp::getSamples() { return numSamples;}

void SetUp::setOutpuFile(QString name) {
    this->outputFile = name;
}

void SetUp::setBackground(bool back) {
    this->background = back;
}
void SetUp::setTopBackground(vec3 color) {
    this->topBackground = color;
}
void SetUp::setDownBackground(vec3 color) {
    this->downBackground = color;
}

void SetUp::setSamples(int s) {
   numSamples = s;
}

void SetUp::setShadows(bool b) {
    shadows = b;
}

void SetUp::setReflections(bool b) {
    reflections = b;
}
void SetUp::setRefractions(bool b) {
    refractions = b;
}

void SetUp::setTextures(bool b) {
    textures = b;
}




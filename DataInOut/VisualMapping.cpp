#include "VisualMapping.hh"


//! [0]
void VisualMapping::read(const QJsonObject &json)
{
    if (json.contains("Real") && json["Real"].isObject()) {
        QJsonObject jobject = json["Real"].toObject();
        if (jobject.contains("minPoint") && jobject["minPoint"].isArray()) {
            QJsonArray objectsArray = jobject["minPoint"].toArray();
            Rxmin = objectsArray[0].toDouble();
            Rzmin = objectsArray[1].toDouble();
         }
        if (jobject.contains("maxPoint") && jobject["maxPoint"].isArray()) {
            QJsonArray objectsArray = jobject["maxPoint"].toArray();
            Rxmax = objectsArray[0].toDouble();
            Rzmax = objectsArray[1].toDouble();
         }
    }
    if (json.contains("Virtual") && json["Virtual"].isObject()) {
        QJsonObject jobject = json["Virtual"].toObject();
        if (jobject.contains("minPoint") && jobject["minPoint"].isArray()) {
            QJsonArray objectsArray = jobject["minPoint"].toArray();
            Vxmin = objectsArray[0].toDouble();
            Vymin = objectsArray[1].toDouble();
            Vzmin = objectsArray[2].toDouble();
         }
        if (jobject.contains("maxPoint") && jobject["maxPoint"].isArray()) {
            QJsonArray objectsArray = jobject["maxPoint"].toArray();
            Vxmax = objectsArray[0].toDouble();
            Vymax = objectsArray[1].toDouble();
            Vzmax = objectsArray[2].toDouble();
         }
    }


}
//! [0]

void VisualMapping::write(QJsonObject &json) const
{
    QJsonObject jobject;
    QJsonArray  objectsArray;
    objectsArray.append(Rxmin); objectsArray.append(Rzmin);
    jobject["minPoint"] = objectsArray;
    QJsonArray objectsArray2;
    objectsArray2.append(Rxmax); objectsArray2.append(Rzmax);
    jobject["maxPoint"] = objectsArray2;
    json["Real"] = jobject;

    QJsonObject jobject2;
    QJsonArray objectsArray3;
    objectsArray3.append(Vxmin); objectsArray3.append(Vymin);objectsArray3.append(Vzmin);
    jobject["minPoint"] = objectsArray3;
    QJsonArray objectsArray4;
    objectsArray4.append(Vxmax); objectsArray4.append(Vzmax);objectsArray4.append(Vzmax);
    jobject["maxPoint"] = objectsArray4;
    json["Virtual"] = jobject2;
}

void VisualMapping::writeAttribute(QJsonObject &attributeJson, int i) const{
    QJsonObject propJson;
    attributeMapping[i]->write(attributeJson);
}

void VisualMapping::readAttribute(const QJsonObject &json) {
    auto atMapping = new AttributeMapping();
    atMapping->read(json);
    attributeMapping.push_back(atMapping);
}

void VisualMapping::printAttribute(int i, int indent) const {
    QTextStream(stdout) << indent << "Attribute:\t \n";
    attributeMapping[i]->print(indent);
}

void VisualMapping::print(int indentation) const
{
    const QString indent(indentation * 2, ' ');
    QTextStream(stdout) << indent << "Real:\t \n";
    QTextStream(stdout) << indent+2 << "minPoint:\t"  << Rxmin<<", "<< Rzmin<<"\n";
    QTextStream(stdout) << indent+2 << "maxPoint:\t"  << Rxmax<<", "<< Rzmax<<"\n";

    QTextStream(stdout) << indent << "Virtual:\t \n";
    QTextStream(stdout) << indent+2 << "minPoint:\t"  << Vxmin<<", "<< Vymin<<", "<< Vzmin<<"\n";
    QTextStream(stdout) << indent+2 << "maxPoint:\t"  << Vxmax<<", "<< Vymax<<", "<< Vzmin<<"\n";


 }


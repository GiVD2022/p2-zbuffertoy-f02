#pragma once

#include <memory>
#include <QObject>
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QTextStream>

class Serializable
{
public:
    virtual void read (const QJsonObject &json) = 0;
    virtual void write (QJsonObject &json) const = 0;
    virtual void print (int indentation) const = 0;
};


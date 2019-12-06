#ifndef JESON2OBJECT_H
#define JESON2OBJECT_H
#include <QMap>
#include <QJsonDocument>
#include <QJsonObject>
#include <mdetail.h>
class Jeson2Object
{
public:
    Jeson2Object();
    Jeson2Object(QString str,QMap<uint, MDetail *> &map);
};

#endif // JESON2OBJECT_H

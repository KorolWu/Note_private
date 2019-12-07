#include "jeson2object.h"

Jeson2Object::Jeson2Object()
{

}

Jeson2Object::Jeson2Object(QString str,QMap<uint, MDetail *> &map)
{
    QByteArray buf = str.toUtf8();
    QJsonDocument jd = QJsonDocument::fromJson(buf);
    if(jd.isObject())
    {
        QJsonObject jo = jd.object();
    }
}
void Jeson2Object::initList() {
    m_iList << "I1" << "I2" << "I3" << "I4" << "I5";

}
void Jeson2Object::parseJsonFile(const QString &fileName)
{
     m_vList << "name" << "url";
    QByteArray buf = fileName.toLatin1();
    QJsonParseError jsonParseError;
    QJsonDocument jsonDocument(QJsonDocument::fromJson(buf, &jsonParseError));
    if(QJsonParseError::NoError != jsonParseError.error)
    {
        qDebug() << QString("JsonParseError: %1").arg(jsonParseError.errorString());
        return;
    }
    QJsonObject rootObject = jsonDocument.object();
    if(!rootObject.keys().contains("sites"))
    {
        qDebug() << "No target value";
        return;
    }
    QJsonValue jsonValue = rootObject.value("sites");
    if(!jsonValue.isArray())
    {
        qDebug() << "No target array";
    }
    QJsonArray jsonArray = jsonValue.toArray();
    for(auto iter = jsonArray.constBegin(); iter != jsonArray.constEnd(); ++iter)
    {
        parseJsonObject(iter);
    }
}
void Jeson2Object::parseJsonObject(QJsonArray::const_iterator iter) {
    QJsonObject jsonObject = (*iter).toObject();
    if(jsonObject.keys().contains("name"))
    {
        qDebug()<<"budeliaol----"<<jsonObject.value("name").toString();
    }
    if(jsonObject.keys().contains("url"))
    {
        qDebug()<<"budeliaol----"<<jsonObject.value("url").toString();
    }

}
void Jeson2Object::parseJsonObjectI(QJsonObject &object)
{
    qDebug() << object.keys();
    for(int i = 0; i < object.keys().size(); ++i)
    {
        QJsonValue jsonValue = object.value(object.keys().at(i));
        if(jsonValue.isObject())
        {
            QJsonObject jsonObject = jsonValue.toObject();
            if(jsonObject.keys().contains("quality"))
            {
                qDebug() << QString("%1 : %2").arg("quality").arg(jsonObject.value("quality").toDouble());
            }
            if(jsonObject.keys().contains("temp"))
            {
                qDebug() << QString("%1 : %2").arg("temp").arg(jsonObject.value("temp").toDouble());
            }
        }
    }
    qDebug() << object.keys();
}
void Jeson2Object::parseJsonObjectV(QJsonObject &object) {
    for(int i = 0; i < object.keys().size(); ++i)
    {
        QJsonValue jsonValue = object.value(object.keys().at(i));
        if(jsonValue.isObject())
        {
            QJsonObject jsonObject = jsonValue.toObject();
            if(jsonObject.keys().contains("value"))
            {

                qDebug() << QString("%1 : %2").arg("value").arg(jsonObject.value("value").toInt());
            }
        }
    }

}

#include "iotsimulation.h"
#include "qiotdevthread.h"
#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonArray>
#include <qDebug>
#include <QFile>
#include <QStringList>
//创建多线程类



CIotSimulation::CIotSimulation(QObject *parent) : QObject(parent)
{
    //初始化经纬度点
    QString PointsPath = QCoreApplication::applicationDirPath();
    PointsPath += "/points.json";
    QFile file(PointsPath);
    if(file.open(QFile::ReadOnly))
    {
        QByteArray array = file.readAll();
        QJsonDocument d = QJsonDocument::fromJson(array);
        QJsonArray sett2 = d.array();
        qDebug()<<sett2;
        for(int i = 0; i < sett2.count(); i++)
        {
            QVariantMap var;
            QJsonValue value = sett2.at(i);
            QVariantMap map = value.toVariant().toMap();
            QString point = map["Point"].toMap()["coordinates"].toString();
            QStringList lonlat = point.split(',');
            if(lonlat.size() != 2)
                continue;
            var["longitude"] = lonlat.at(0).toDouble();
            var["latitude"] = lonlat.at(1).toDouble();
            mlatlonList.append(var);
        }
    }
    //mlatlonList
}

void CIotSimulation::SimulationDev(const QVariant& var)
{
    QVariantMap map = var.toMap();
    qDebug()<<"开始设备仿真！！";
    CQIotDevThread* iotDev = new CQIotDevThread();
    iotDev->strHost = "x8kbk8.messaging.internetofthings.ibmcloud.com";
    iotDev->port = 1883;
    iotDev->strClientId = map["clientId"].toString();
    iotDev->strUsername = "use-token-auth";
    iotDev->strPwd = map["authToken"].toString();

    iotDev->mAliveTi = 60;

    iotDev->mConfig = mDevTConMaps[map["typeId"].toString()];
    //设置数据
    if(mlatlonList.size() != 0)
    {
        iotDev->lat = mlatlonList.at(mIotDevList.size()%mlatlonList.size()).toMap()["longitude"].toDouble();
        iotDev->lon = mlatlonList.at(mIotDevList.size()%mlatlonList.size()).toMap()["latitude"].toDouble();
    }
    mIotDevList.append(iotDev);
    iotDev->start();
}
void CIotSimulation::setConfig(const QString& DeviceId,
                               const simulationConfig& config)
{
    mDevTConMaps[DeviceId] = config;
}

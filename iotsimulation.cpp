#include "iotsimulation.h"
#include "qiotdevthread.h"
#include <qDebug>
//创建多线程类



CIotSimulation::CIotSimulation(QObject *parent) : QObject(parent)
{
}

void CIotSimulation::SimulationDev(const QVariant& var)
{
    QVariantMap map = var.toMap();
    qDebug()<<"开始设备仿真！！";
    CQIotDevThread* iotDev = new CQIotDevThread();
    mIotDevList.append(iotDev);
    iotDev->strHost = "x8kbk8.messaging.internetofthings.ibmcloud.com";
    iotDev->port = 1883;
    iotDev->strClientId = map["clientId"].toString();
    iotDev->strUsername = "use-token-auth";
    iotDev->strPwd = map["authToken"].toString();
    iotDev->mAliveTi = 60;

    iotDev->start();
}

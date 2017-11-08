#ifndef CIOTSIMULATION_H
#define CIOTSIMULATION_H

#include <QObject>
#include <QList>
#include <QMap>
#include <QVariant>
#include "types.h"
class CQIotDevThread;
class CIotSimulation : public QObject
{
    Q_OBJECT
public:
    explicit CIotSimulation(QObject *parent = 0);
    //仿真一个设备！
    void SimulationDev(const QVariant& var);



    void setConfig(const QString& DeviceId, const simulationConfig& config);
private:
    //经纬度列表
    QVariantList mlatlonList;


    //设备列表
    QList<CQIotDevThread*> mIotDevList;
    QMap<QString, simulationConfig> mDevTConMaps;
signals:

public slots:
};

#endif // CIOTSIMULATION_H

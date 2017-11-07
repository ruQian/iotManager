#ifndef CIOTSIMULATION_H
#define CIOTSIMULATION_H

#include <QObject>
#include <QList>

class CQIotDevThread;
class CIotSimulation : public QObject
{
    Q_OBJECT
public:
    explicit CIotSimulation(QObject *parent = 0);
    //仿真一个设备！
    void SimulationDev(const QVariant& var);
public:
    //设备列表
    QList<CQIotDevThread*> mIotDevList;
signals:

public slots:
};

#endif // CIOTSIMULATION_H

#ifndef CIOTSIMULATION_H
#define CIOTSIMULATION_H

#include <QObject>
#include "mqtt/qmqtt.h"
class CIotSimulation : public QObject
{
    Q_OBJECT
public:
    explicit CIotSimulation(QObject *parent = 0);

signals:

public slots:
};

#endif // CIOTSIMULATION_H

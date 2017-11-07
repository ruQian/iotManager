#include "iotsimulation.h"

CIotSimulation::CIotSimulation(QObject *parent) : QObject(parent)
{


    QMQTT::Client *client = new QMQTT::Client(QHostAddress::LocalHost, 1883);


}


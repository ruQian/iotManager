#ifndef CDEVMANAGERTHREAD_H
#define CDEVMANAGERTHREAD_H

#include <QThread>
#include "types.h"
class CDevManager;
class CDevManagerThread : public QThread
{
    Q_OBJECT
public:
    explicit CDevManagerThread(QObject *parent = 0);

    int operType;
    CDevManager* manager;
public:
    virtual void run();
signals:
    void signal_DeviceTypes(const QList<DeviceType>&);
    void signal_Devices(const QList<DeviceInfo>&);
public slots:
};

#endif // CDEVMANAGERTHREAD_H

#include "cdevmanagerthread.h"
#include "devmanager.h"
#include <QMetaType>
//#include <>
CDevManagerThread::CDevManagerThread(QObject *parent) : QThread(parent)
{
    moveToThread(this);
    manager = nullptr;
    qRegisterMetaType<QList<DeviceType>>("QList<DeviceType>");
    qRegisterMetaType<QList<DeviceInfo>>("QList<DeviceInfo>");
}
void CDevManagerThread::run()
{
    if(!manager)
        return ;
    switch(operType)
    {
    case 1:
        {
            QList<DeviceType> devTypes = manager->getDevType();
            emit signal_DeviceTypes(devTypes);
            disconnect(SIGNAL(signal_DeviceTypes(const QList<DeviceType>&)));
        }
        break;
    case 2:
        {
            QList<DeviceInfo> devices = manager->GetDevices();
            emit signal_Devices(devices);
            disconnect(SIGNAL(signal_Devices(const QList<DeviceInfo>&)));
        }
        break;
    }
}






















#ifndef CDEVMANAGER_H
#define CDEVMANAGER_H

#include <QObject>
#include "types.h"

class QNetworkRequest;
class CDevManagerThread;
class CDevManager : public QObject
{
    Q_OBJECT
public:
    explicit CDevManager(QObject *parent = 0);

public:
    //设置主机
    void setHost(const QString& strHost);
    //设置用户名密码
    void setUserPwd(const QString& strUser, const QString& strPwd);
    //获取设备类型信息
    QList<DeviceType> getDevType();
    void getDevTypeAsyn(QObject* ob, const char* slot);
    //获取设备信息
    void GetDevicesAsyn(QObject* ob, const char* slot);
    QList<DeviceInfo> GetDevices(const QString& bookMark = QString());
private:
    void setUserPwd(QNetworkRequest& request);
private:
    CDevManagerThread* toperThread;
    QString mStrHost;
    QString mStrUser;
    QString mStrPwd;
signals:

public slots:
};

#endif // CDEVMANAGER_H

#include "devmanager.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonArray>
#include "qeventloop.h"
#include <QJsonDocument>
#include "cdevmanagerthread.h"
#include <qDebug>
#include <QScopedPointer>
CDevManager::CDevManager(QObject *parent) : QObject(parent)
{
     toperThread = new CDevManagerThread(this);
     toperThread->manager = this;
     toperThread->operType = 1;
}

void CDevManager::setUserPwd(QNetworkRequest& request)
{
    QString strAuth = "Basic ";
    QString strUserPwd = mStrUser;
    strUserPwd += ":";
    strUserPwd += mStrPwd;
    QByteArray arrBasic = strUserPwd.toUtf8();
    QString strBasic = arrBasic.toBase64();
    strAuth += strBasic;
    qDebug()<<strAuth;
    request.setRawHeader("Authorization",strAuth.toUtf8());
}


//设置主机
void CDevManager::setHost(const QString& strHost)
{
    mStrHost = strHost;
}
//设置用户名密码
void CDevManager::setUserPwd(const QString& strUser, const QString& strPwd)
{
    mStrUser = strUser;
    mStrPwd = strPwd;
}


void CDevManager::getDevTypeAsyn(QObject* ob, const char* slot)
{
    toperThread->operType = 1;
    connect(toperThread,SIGNAL(signal_DeviceTypes(const QList<DeviceType>&)),
            ob, slot);
    toperThread->start();
    return ;
}
QList<DeviceType> CDevManager::getDevType()
{
    QScopedPointer<QNetworkAccessManager> man(new QNetworkAccessManager());
    QList<DeviceType> devTypeList;
    devTypeList.clear();
    QString strUrl = "https://";
    strUrl += mStrHost;
    strUrl += "/api/v0002/device/types";
    qDebug()<<strUrl;
    QNetworkRequest request;
    setUserPwd(request);
    request.setUrl(QUrl(strUrl));
    QNetworkReply* reply = man->get(request);
    QEventLoop eventLoop;
    connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
    QByteArray replyData = reply->readAll();

    qDebug()<<replyData;
    reply->deleteLater();
    reply = nullptr;
    QJsonDocument d = QJsonDocument::fromJson(replyData);
    QJsonObject sett2 = d.object();
    QJsonValue value = sett2.value(QString("results"));
    QJsonArray item = value.toArray();
    for(int i = 0; i < item.count(); ++i)
    {
        QJsonValue value = item.at(i);
        QString strDevice = value.toObject()["id"].toString();
        qDebug()<<strDevice;
        //AddDeviceType(strDevice);
        //
        DeviceType devtype;
        devtype.mDevType = strDevice;
        devTypeList.append(devtype);
    }
    return devTypeList;
}
void CDevManager::GetDevicesAsyn(QObject* ob, const char* slot)
{
    toperThread->operType = 2;
    connect(toperThread,SIGNAL(signal_Devices(const QList<DeviceInfo>&)),
            ob, slot);
    toperThread->start();
    return ;
}
QList<DeviceInfo> CDevManager::GetDevices(const QString& bookMark)
{
    QScopedPointer<QNetworkAccessManager> man(new QNetworkAccessManager());
    QList<DeviceInfo> devList;
    QString strUrl = "https://";
    strUrl += mStrHost;
    strUrl += "/api/v0002/bulk/devices";
    strUrl += "?_limit=100";
    if(!bookMark.isEmpty())
    {
        strUrl+="&_bookmark=";
        strUrl+=bookMark;
    }
    qDebug()<<strUrl;
    QNetworkRequest request;
    setUserPwd(request);
    request.setUrl(QUrl(strUrl));
    QNetworkReply* reply = man->get(request);
    QEventLoop eventLoop;
    connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
    qDebug()<<reply->error();
    QByteArray replyData = reply->readAll();
    reply->deleteLater();
    reply = nullptr;
    QJsonDocument d = QJsonDocument::fromJson(replyData);
    QJsonObject sett2 = d.object();
    QJsonValue value = sett2.value(QString("results"));
    qDebug()<<value;
    QJsonArray item = value.toArray();
    qDebug()<<replyData;

    for(int i = 0; i < item.count(); ++i)
    {
        DeviceInfo devInfo;
        QJsonValue value = item.at(i);

        QString strDevice = value.toObject()["deviceId"].toString();
        qDebug()<<strDevice;

        QString strDeviceType = value.toObject()["typeId"].toString();
       // if(DeviceType == strDeviceType)
        //{
        //    AddDeviceName(strDeviceType, strDevice);
        //}
        devInfo.mDevType = strDeviceType;
        devInfo.mDevID = strDevice;
        devList.append(devInfo);
    }
    QString strMark = sett2.value(QString("bookmark")).toString();
    if(!strMark.isEmpty())
        devList.append(GetDevices(strMark));
    return devList;
}

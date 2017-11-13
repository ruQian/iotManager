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

void CDevManager::CreateDevType(const DeviceType& devType)
{
    QString data = QString("{  \
                            \"id\": \"%1\",\
                           \"description\": \"21 \",\
                           \"classId\": \"Device\",\
                           \"deviceInfo\": {\
                             \"serialNumber\": \"100087\",\
                             \"manufacturer\": \"12\",\
                             \"model\": \"12\",\
                             \"deviceClass\": \"12\",\
                             \"description\": \"12\",\
                             \"fwVersion\": \"12\",\
                             \"hwVersion\": \"12\",\
                             \"descriptiveLocation\": \"12\"\
                           },\
                           \"metadata\": {\
                             \"a\": \"12\",\
                             \"b\": \"12\"\
                           }\
                         }").arg(devType.mDevType);
    QScopedPointer<QNetworkAccessManager> man(new QNetworkAccessManager());
    QString strUrl = "https://";
    strUrl += mStrHost;
    strUrl += "/api/v0002/device/types";
    qDebug()<<strUrl;
    QNetworkRequest request;
    setUserPwd(request);
    request.setRawHeader("Content-Type", "application/json");
    QString strLen = QString("%1").arg(data.toUtf8().size());
    request.setRawHeader("Content-Length", strLen.toUtf8());



    request.setUrl(QUrl(strUrl));
    QNetworkReply* reply = man->post(request, data.toUtf8());
    QEventLoop eventLoop;
    connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
    qDebug()<<reply->error();
    QByteArray replyData = reply->readAll();
    reply->deleteLater();
    reply = nullptr;
    qDebug()<<replyData;
}


void CDevManager::GetDevicesAsyn(QObject* ob, const char* slot)
{
    toperThread->operType = 2;
    connect(toperThread,SIGNAL(signal_Devices(const QList<DeviceInfo>&)),
            ob, slot);
    toperThread->start();
    return ;
}
QString CDevManager::DeleteDevType(const QString& devType)
{
    QScopedPointer<QNetworkAccessManager> man(new QNetworkAccessManager());
    QString strUrl = "https://";
    strUrl += mStrHost;
    strUrl += "/api/v0002/device/types/";
    strUrl += devType;

    qDebug()<<strUrl;
    QNetworkRequest request;
    setUserPwd(request);
    request.setUrl(QUrl(strUrl));
    QNetworkReply* reply = man->deleteResource(request);
    QEventLoop eventLoop;
    connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
    qDebug()<<reply->error();
    return QString();//reply->error();
}

QString CDevManager::DeleteDev(const DeviceInfo& devInfo)
{
    //device/types/{typeId}/devices/{deviceId}
    QScopedPointer<QNetworkAccessManager> man(new QNetworkAccessManager());
    QString strUrl = "https://";
    strUrl += mStrHost;
    strUrl += "/api/v0002/device/types/";
    strUrl += devInfo.mDevType;
    strUrl += "/devices/";
    strUrl += devInfo.mDevID;

    qDebug()<<strUrl;
    QNetworkRequest request;
    setUserPwd(request);
    request.setUrl(QUrl(strUrl));
    QNetworkReply* reply = man->deleteResource(request);
    QEventLoop eventLoop;
    connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
    qDebug()<<reply->error();
    return QString();//reply->error();
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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <adddevicesdialog.h>
#include "adddevicedialog.h"
#include "settingdialog.h"
#include "adddevtdialog.h"
#include <QNetworkRequest>
#include <QAuthenticator>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QMouseEvent>
#include <QJsonObject>
#include <QJsonArray>
#include <QMouseEvent>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mSettingDlg = new CSettingDialog(this);

    ///
    man = new QNetworkAccessManager(this);

    //connect widget and treewidget
    connect(ui->treeWidget, SIGNAL(signal_rightPress(QMouseEvent*)),
            this, SLOT(slot_mousePressEvent(QMouseEvent*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::AddDeviceType(const QString& DeviceType)
{
    QStringList strList;
    strList<<DeviceType;
    QTreeWidgetItem* item = new QTreeWidgetItem(strList);
    ui->treeWidget->addTopLevelItem(item);
    return;
}
void MainWindow::AddDeviceName(const QString& DeviceType,
                                const QString& DeviceName)
{
    for(int i = 0; i < ui->treeWidget->topLevelItemCount(); i++)
    {
        QTreeWidgetItem* item = ui->treeWidget->topLevelItem(i);
        if(item != nullptr && item->text(0) == DeviceType)
        {
            QStringList strList;
            strList<<DeviceName;
            QTreeWidgetItem* itemChild = new QTreeWidgetItem(strList);
            item->addChild(itemChild);
        }
    }
    return ;
}
void MainWindow::on_action_2_triggered()
{
    ui->treeWidget->clear();
    devTypeList.clear();

    QString strUrl = "https://";
    strUrl += mSettingDlg->mOrg;
    strUrl += mSettingDlg->mHost;
    strUrl += "/api/v0002/device/types";
    qDebug()<<strUrl;
    QNetworkRequest request;
    request.setRawHeader("Authorization","Basic YS14OGtiazgtcmtxYjR4MW53NzpOK3dIIXVRYysmanZvR1N3a0U=");
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
    QJsonArray item = value.toArray();
    for(int i = 0; i < item.count(); ++i)
    {
        QJsonValue value = item.at(i);

        QString strDevice = value.toObject()["id"].toString();
        qDebug()<<strDevice;

        AddDeviceType(strDevice);
        //
        DeviceType devtype;
        devtype.mDevType = strDevice;
        devTypeList.append(devtype);
        GetDeviceByType(strDevice);
    }
}
void MainWindow::GetDeviceByType(const QString& DeviceType)
{
    QString strUrl = "https://";
    strUrl += mSettingDlg->mOrg;
    strUrl += mSettingDlg->mHost;
    strUrl += "/api/v0002/device/types/";
    strUrl += DeviceType;
    strUrl += "/devices";
    qDebug()<<strUrl;
    QNetworkRequest request;
    request.setRawHeader("Authorization","Basic YS14OGtiazgtcmtxYjR4MW53NzpOK3dIIXVRYysmanZvR1N3a0U=");
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
    for(int i = 0; i < item.count(); ++i)
    {
        QJsonValue value = item.at(i);

        QString strDevice = value.toObject()["deviceId"].toString();
        qDebug()<<strDevice;

        AddDeviceName(DeviceType, strDevice);

    }
}


void MainWindow::on_action_triggered()
{
    mSettingDlg->exec();
}



void MainWindow::on_actionADevT_triggered()
{
    CAddDevTDialog dlg;
    connect(&dlg, SIGNAL(signal_addDevType(QList<DeviceType>)),
            this, SLOT(slot_addDevType(QList<DeviceType>)));
    dlg.exec();
}

void MainWindow::on_actionADev_triggered()
{
    CAddDeviceDialog dlg;
    dlg.initDevType(devTypeList);
    int res = dlg.exec();
    if(res == 8)
    {
        QList<DeviceInfo> devList;
        DeviceInfo devinfo;
        devinfo.mDevType = dlg.strDeviceType;
        devinfo.mDevID = dlg.strDeviceID;
        devList<<devinfo;
        slot_addDev(devList);
    }
}

void MainWindow::slot_addDevType(QList<DeviceType> devTList)
{
    for(QList<DeviceType>::Iterator it = devTList.begin();
        it != devTList.end(); ++it)
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
                             }").arg((*it).mDevType);



        QString strUrl = "https://";
        strUrl += mSettingDlg->mOrg;
        strUrl += mSettingDlg->mHost;
        strUrl += "/api/v0002/device/types";
        qDebug()<<strUrl;
        QNetworkRequest request;
        request.setRawHeader("Authorization","Basic YS14OGtiazgtcmtxYjR4MW53NzpOK3dIIXVRYysmanZvR1N3a0U=");
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
}


void MainWindow::slot_addDev(const QList<DeviceInfo>& deviceInfos)
{
    for(QList<DeviceInfo>::const_iterator it = deviceInfos.begin();
        it != deviceInfos.end(); ++it)
    {
        QString data = QString("{\
                               \"deviceId\": \"%1\",\
                               \"deviceInfo\": {\
                                 \"serialNumber\": \"12\",\
                                 \"manufacturer\": \"12\",\
                                 \"model\": \"12\",\
                                 \"deviceClass\": \"12\",\
                                 \"description\": \"12\",\
                                 \"fwVersion\": \"12\",\
                                 \"hwVersion\": \"12\",\
                                 \"descriptiveLocation\": \"12\"\
                               },\
                               \"location\": {\
                                 \"longitude\": 0,\
                                 \"latitude\": 0,\
                                 \"elevation\": 0,\
                                 \"accuracy\": 0,\
                                 \"measuredDateTime\": \"2017-11-06T07:24:08.631Z\"\
                               },\
                               \"metadata\": {}\
                             }").arg((*it).mDevID);



        QString strUrl = "https://";
        strUrl += mSettingDlg->mOrg;
        strUrl += mSettingDlg->mHost;
        strUrl += "/api/v0002/device/types/";
        strUrl += (*it).mDevType;
        strUrl += "/devices";
        qDebug()<<strUrl;
        QNetworkRequest request;
        request.setRawHeader("Authorization","Basic YS14OGtiazgtcmtxYjR4MW53NzpOK3dIIXVRYysmanZvR1N3a0U=");
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
}
void MainWindow::on_action_3_triggered()
{
    //批量添加设备
    CAddDevicesDialog dlg;
    dlg.initDevType(devTypeList);
    int res = dlg.exec();
    if(res == 8)
    {
        //创建设备
        QString strName = dlg.strPreName;
        int strCount = dlg.strCount.toInt();
        QString strDevType = dlg.strDevType;
        for(int i = 0; i< strCount; i++)
        {
            QString strDevID = QString("%1_%2").arg(strName).arg(i);

            QList<DeviceInfo> devList;
            DeviceInfo devinfo;
            devinfo.mDevType = strDevType;
            devinfo.mDevID = strDevID;
            devList<<devinfo;
            slot_addDev(devList);
        }
    }
}

void MainWindow::slot_mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::RightButton)
    {
        QTreeWidgetItem* item = ui->treeWidget->itemAt(event->pos());
        if(item != nullptr)
        {
            if(item->parent() == nullptr)
            {
               //一级的 ITEM
                QMenu menu;
                menu.addAction("添加该类型设备");
                menu.exec(event->globalPos());
            }else
            {

            }
        }else
        {
            QMenu menu;
            menu.addAction("添加设备类型");
            menu.exec(event->globalPos());
        }
    }
    return ;
}






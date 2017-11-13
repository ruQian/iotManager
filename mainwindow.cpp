#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <adddevicesdialog.h>
#include "adddevicedialog.h"
#include "settingdialog.h"
#include "adddevtsigdlg.h"
#include "SimulationSetDialog.h"
#include <QNetworkRequest>
#include <QAuthenticator>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QMouseEvent>
#include <QJsonObject>
#include <QJsonArray>
#include <QResizeEvent>
#include <QMessageBox>
#include <QMouseEvent>
#include "devmanager.h"
#include "waitwidget.h"
#include <QMenu>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    deviceInfoPath = QCoreApplication::applicationDirPath();
    deviceInfoPath += "/devicesInfo.txt";
    qDebug()<<deviceInfoPath;
    mSettingDlg = new CSettingDialog(this);
    ///
    man = new QNetworkAccessManager();
    waitWidget = new CWaitWidget(this);
    waitWidget->hide();

    //////////
    devManager = new CDevManager();
    //////////
    //connect widget and treewidget
    connect(ui->treeWidget, SIGNAL(signal_rightPress(QMouseEvent*)),
            this, SLOT(slot_mousePressEvent(QMouseEvent*)));

    ui->treeWidget->headerItem()->setText(0, QString("设备列表"));

    devManager->setHost(mSettingDlg->mHost);
    devManager->setUserPwd(mSettingDlg->mUserName, mSettingDlg->mPassword);
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
    showWaitWidget();
    devManager->getDevTypeAsyn(this, SLOT(slot_DeviceTypes(const QList<DeviceType>&)));
}
void MainWindow::GetDeviceByType()
{
    showWaitWidget();
    devManager->GetDevicesAsyn(this, SLOT(slot_Devices(const QList<DeviceInfo>&)));
    /*
    QList<DeviceInfo> devList = devManager->GetDevices();
    for(QList<DeviceInfo>::Iterator it = devList.begin();
                    it != devList.end(); it++)
    {
        AddDeviceName((*it).mDevType, (*it).mDevID);
    }*/
}

void MainWindow::slot_DeviceTypes(const QList<DeviceType>& devTypes)
{
    ui->treeWidget->clear();
    devTypeList.clear();

    devTypeList = devTypes;
    for(QList<DeviceType>::Iterator it = devTypeList.begin();
                    it != devTypeList.end(); it++)
    {
        AddDeviceType((*it).mDevType);
    }
    hideWaitWidget();
    GetDeviceByType();
}
void MainWindow::slot_Devices(const QList<DeviceInfo>& devList)
{
    for(QList<DeviceInfo>::const_iterator it = devList.begin();
                    it != devList.end(); it++)
    {
        AddDeviceName((*it).mDevType, (*it).mDevID);
    }
    hideWaitWidget();
}

void MainWindow::on_action_triggered()
{
    mSettingDlg->exec();
    devManager->setHost(mSettingDlg->mHost);
    devManager->setUserPwd(mSettingDlg->mUserName, mSettingDlg->mPassword);
}



void MainWindow::on_actionADevT_triggered()
{
//    CAddDevTDialog dlg;
//    connect(&dlg, SIGNAL(signal_addDevType(QList<DeviceType>)),
//            this, SLOT(slot_addDevType(QList<DeviceType>)));
    CAddDevTSigDlg dlg;
    if(8 == dlg.exec())
    {
        DeviceType devT;
        devT.mDevType = dlg.strDevType;
        devT.mDevDes = dlg.strDevDes;
        devManager->CreateDevType(devT);
    }
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
        strUrl += mSettingDlg->mHost;
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
        strUrl += mSettingDlg->mHost;
        strUrl += "/api/v0002/device/types/";
        strUrl += (*it).mDevType;
        strUrl += "/devices";
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
        //qDebug()<<replyData;

        QJsonDocument d = QJsonDocument::fromJson(replyData);
        QJsonObject sett2 = d.object();

        QVariantMap mapInfo;

        qDebug()<<sett2.value(QString("authToken")).toString();
        mapInfo["clientId"] =  sett2.value(QString("clientId")).toString();
        mapInfo["typeId"] = sett2.value(QString("typeId")).toString();
        mapInfo["deviceId"] = sett2.value(QString("deviceId")).toString();
        mapInfo["authToken"] = sett2.value(QString("authToken")).toString();


        qDebug()<<mapInfo;


        //追加到文件里面
        QFile file(deviceInfoPath);
        file.open(QFile::ReadWrite);
        QByteArray bytes = file.readAll();
        file.resize(0);
        QJsonDocument filed = QJsonDocument::fromJson(bytes);
        QJsonArray arf = filed.array();
        QJsonValue jvalue = QJsonValue::fromVariant(mapInfo);
        arf.append(jvalue);
        filed.setArray(arf);
        bytes = filed.toJson();
        file.write(bytes);
        file.close();
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
            QString itemName = item->text(0);
            if(item->parent() == nullptr)
            {
               //一级的 ITEM
                QMenu menu;
                menu.addAction("添加该类型设备");
                menu.addAction("批量添加该类型设备");
                menu.addAction("仿真该类型所有设备");
                menu.addAction("仿真数据设置");
                menu.addAction("删除设备类型");
                QAction* ac = menu.exec(event->globalPos());
                if(ac != nullptr)
                {
                    if(ac->text() == QString("删除设备类型"))
                    {
                        //得到该类型下的所有节点
                        int childCount = item->childCount();
                        for(int i = 0; i < childCount; ++i)
                        {
                            QTreeWidgetItem* hildItem = item->child(i);
                            if(hildItem != nullptr)
                            {
                                //设备ID
                                QString deviceId = hildItem->text(0);
                                DeviceInfo devInfo;
                                devInfo.mDevType = itemName;
                                devInfo.mDevID = deviceId;
                                devManager->DeleteDev(devInfo);
                            }
                        }
                        devManager->DeleteDevType(itemName);
                    }
                    if(ac->text() == QString("仿真数据设置"))
                    {
                        CSimulationSetDialog dlg;
                        if(8 == dlg.exec())
                        {
                            simulationConfig config = dlg.GetConfig();
                            mIotSimulation.setConfig(itemName, config);
                        }

                    }
                    if(ac->text() == QString("添加该类型设备"))
                    {
                        //同步服务器数据
                        CAddDeviceDialog dlg;
                        QList<DeviceType> devTypeListTmp;
                        DeviceType deviceType;
                        deviceType.mDevType = itemName;
                        devTypeListTmp<<deviceType;
                        dlg.initDevType(devTypeListTmp);
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
                    if(ac->text() == QString("批量添加该类型设备"))
                    {
                        //批量添加设备
                        CAddDevicesDialog dlg;
                        QList<DeviceType> devTypeListTmp;
                        DeviceType deviceType;
                        deviceType.mDevType = itemName;
                        devTypeListTmp<<deviceType;
                        dlg.initDevType(devTypeListTmp);
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
                    if(ac->text() == QString("仿真该类型所有设备"))
                    {
                        //得到该类型下的所有节点
                        int childCount = item->childCount();
                        for(int i = 0; i < childCount; ++i)
                        {
                            QTreeWidgetItem* hildItem = item->child(i);
                            if(hildItem != nullptr)
                            {
                                //设备ID
                                QString deviceId = hildItem->text(0);

                                QFile file(deviceInfoPath);
                                file.open(QFile::ReadWrite);
                                QByteArray bytes = file.readAll();
                                QJsonDocument filed = QJsonDocument::fromJson(bytes);
                                QJsonArray arf = filed.array();
                                //
                                QVariantList devInfoList = arf.toVariantList();
                                QVariantList::Iterator it = devInfoList.begin();
                                for(;it != devInfoList.end(); ++it)
                                {
                                    QVariantMap map = (*it).toMap();
                                    if(map["deviceId"].toString() == deviceId &&
                                           map["typeId"].toString() == itemName)
                                    {
                                        SimulationDev(map);
                                        //设置颜色
                                        QColor color(0,205,0);
                                        hildItem->setTextColor(0, color);
                                        hildItem->setToolTip(0, QString("正在仿真..."));
                                        break;
                                    }
                                }
                                if(it == devInfoList.end())
                                {
                                    QColor color(205,38,38);
                                    hildItem->setTextColor(0, color);
                                    hildItem->setToolTip(0, QString("仿真失败 本地没有发现key"));
                                }

                            }
                        }



                    }
                }else
                {

                }
            }else
            {

            }
        }else
        {
            QMenu menu;
            menu.addAction("同步服务器数据");
            menu.addAction("添加设备类型");
            qDebug()<<"-------------------------------------------";
            QAction* ac = menu.exec(event->globalPos());
            if(ac != nullptr)
            {
                qDebug()<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
                if(ac->text() == QString("同步服务器数据"))
                {
                    //同步服务器数据
                    on_action_2_triggered();
                }
                if(ac->text() == QString("添加设备类型"))
                {
                    on_actionADevT_triggered();
                }
            }
        }
    }
    return ;
}

void MainWindow::SimulationDev(const QVariant& var)
{
    QString strErr;
    mIotSimulation.SimulationDev(var, strErr);
}
void MainWindow::setUserPwd(QNetworkRequest& request)
{
    QString strAuth = "Basic ";
    QString strUserPwd = mSettingDlg->mUserName;
    strUserPwd += ":";
    strUserPwd += mSettingDlg->mPassword;
    QByteArray arrBasic = strUserPwd.toUtf8();
    QString strBasic = arrBasic.toBase64();
    strAuth += strBasic;
    qDebug()<<strAuth;
    request.setRawHeader("Authorization",strAuth.toUtf8());
}
void MainWindow::resizeEvent(QResizeEvent* e)
{
    waitWidget->resize(e->size());
}
void MainWindow::showWaitWidget()
{
    QSize size = this->size();
    waitWidget->resize(size);
    waitWidget->show();
}
void MainWindow::hideWaitWidget()
{
    waitWidget->hide();
}
void MainWindow::on_action_4_triggered()
{
    QMessageBox::about(NULL, "About", "<font color='red'>bluemix iot设备仿真软件V0.1(长城数字)</font>");
}

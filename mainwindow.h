#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include "types.h"

namespace Ui {
class MainWindow;
}

class CSettingDialog;
class QNetworkAccessManager;
class QNetworkReply;
class QAuthenticator;




class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public:
private slots:
    void on_action_2_triggered();
    void on_action_triggered();

    void on_actionADevT_triggered();

    void on_actionADev_triggered();

    //添加设备类型到服务器
    void slot_addDevType(QList<DeviceType> devTList);

    //添加设备到服务器
    void slot_addDev(const QList<DeviceInfo>& deviceInfos);
    //
    void on_action_3_triggered();

private:
    void AddDeviceType(const QString& DeviceType);
    void AddDeviceName(const QString& DeviceType, const QString& DeviceName);
    void GetDeviceByType(const QString& DeviceType);
private:
    CSettingDialog* mSettingDlg;
    QNetworkAccessManager* man;
    QString hosts;
public:
    QList<DeviceType> devTypeList;
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

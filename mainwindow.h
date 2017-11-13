#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include "types.h"
#include "iotsimulation.h"
namespace Ui {
class MainWindow;
}

class CSettingDialog;
class QNetworkAccessManager;
class QNetworkReply;
class QAuthenticator;
class QNetworkRequest;
class CDevManager;
class CWaitWidget;

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


    void slot_mousePressEvent(QMouseEvent* event);


    void on_action_4_triggered();

    //
    void slot_DeviceTypes(const QList<DeviceType>&);
    void slot_Devices(const QList<DeviceInfo>&);

private:
    void AddDeviceType(const QString& DeviceType);
    void AddDeviceName(const QString& DeviceType, const QString& DeviceName);
    void GetDeviceByType();
    //仿真一个设备！
    void SimulationDev(const QVariant& var);

    void setUserPwd(QNetworkRequest& request);
private:
    void showWaitWidget();
    void hideWaitWidget();
private:
    CWaitWidget* waitWidget;
    CDevManager* devManager;
    CSettingDialog* mSettingDlg;
    QNetworkAccessManager* man;
    QString hosts;
    //仿真类
    CIotSimulation mIotSimulation;
public:
    //存放创建设备的信息文件
    QString deviceInfoPath;
    QList<DeviceType> devTypeList;
protected:
    void resizeEvent(QResizeEvent* e);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

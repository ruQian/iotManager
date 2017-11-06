#ifndef ADDDEVICEDIALOG_H
#define ADDDEVICEDIALOG_H

#include <QDialog>
#include "types.h"
namespace Ui {
class CAddDeviceDialog;
}

class CAddDeviceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CAddDeviceDialog(QWidget *parent = 0);
    ~CAddDeviceDialog();

    void initDevType(const QList<DeviceType>& devTypeList);

    QString strDeviceType;
    QString strDeviceID;
private slots:
    void on_pushButton_clicked();

private:
    Ui::CAddDeviceDialog *ui;
};

#endif // ADDDEVICEDIALOG_H

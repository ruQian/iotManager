#ifndef ADDDEVICESDIALOG_H
#define ADDDEVICESDIALOG_H

#include <QDialog>
#include "types.h"

namespace Ui {
class CAddDevicesDialog;
}

class CAddDevicesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CAddDevicesDialog(QWidget *parent = 0);
    ~CAddDevicesDialog();

    void initDevType(const QList<DeviceType>& devTypeList);

public:
    QString strDevType;
    QString strCount;
    QString strPreName;
private slots:
    void on_pushButton_clicked();

private:
    Ui::CAddDevicesDialog *ui;
};

#endif // ADDDEVICESDIALOG_H

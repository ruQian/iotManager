#ifndef ADDDEVTDIALOG_H
#define ADDDEVTDIALOG_H

#include <QDialog>
#include "types.h"

namespace Ui {
class CAddDevTDialog;
}

class CAddDevTDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CAddDevTDialog(QWidget *parent = 0);
    ~CAddDevTDialog();
Q_SIGNALS:
    void signal_addDevType(QList<DeviceType>);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::CAddDevTDialog *ui;
};

#endif // ADDDEVTDIALOG_H

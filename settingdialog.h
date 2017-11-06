#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
namespace Ui {
class CSettingDialog;
}

class CSettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CSettingDialog(QWidget *parent = 0);
    ~CSettingDialog();

private slots:
    void on_pushButton_clicked();
public Q_SLOTS:
    virtual int exec();
public:
    QString mOrg;
    QString mHost;
    QString mUserName;
    QString mPassword;
private:
    Ui::CSettingDialog *ui;
};

#endif // SETTINGDIALOG_H

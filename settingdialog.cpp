#include "settingdialog.h"
#include "ui_settingdialog.h"
#include <QSettings>
CSettingDialog::CSettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CSettingDialog)
{
    ui->setupUi(this);

    QSettings *reg = new QSettings("HKEY_CURRENT_USER\\Software\\iotManager",
    QSettings::NativeFormat);
    mHost = reg->value("host","demo.internetofthings.ibmcloud.com").toString();
    mUserName = reg->value("user").toString();
    mPassword = reg->value("passwd").toString();
    delete reg;
}

CSettingDialog::~CSettingDialog()
{
    delete ui;
}

void CSettingDialog::on_pushButton_clicked()
{
    QSettings *reg = new QSettings("HKEY_CURRENT_USER\\Software\\iotManager",
    QSettings::NativeFormat);
    mHost = ui->lineEdit_2->text();
    mUserName = ui->lineEdit_3->text();
    mPassword = ui->lineEdit_4->text();
    reg->setValue("host",mHost);
    reg->setValue("user",mUserName);
    reg->setValue("passwd",mPassword);
    delete reg;
    done(0);
}
int CSettingDialog::exec()
{
    ui->lineEdit_2->setText(mHost);
    ui->lineEdit_3->setText(mUserName);
    ui->lineEdit_4->setText(mPassword);
    return QDialog::exec();
}





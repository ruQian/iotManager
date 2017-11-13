#include "settingdialog.h"
#include "ui_settingdialog.h"

CSettingDialog::CSettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CSettingDialog)
{
    ui->setupUi(this);
    mHost = "x8kbk8.internetofthings.ibmcloud.com";
    mUserName = "a-x8kbk8-rkqb4x1nw7";
    mPassword = "N+wH!uQc+&jvoGSwkE";
}

CSettingDialog::~CSettingDialog()
{
    delete ui;
}

void CSettingDialog::on_pushButton_clicked()
{
    mHost = ui->lineEdit_2->text();
    mUserName = ui->lineEdit_3->text();
    mPassword = ui->lineEdit_4->text();

    done(0);
}
int CSettingDialog::exec()
{
    ui->lineEdit_2->setText(mHost);
    ui->lineEdit_3->setText(mUserName);
    ui->lineEdit_4->setText(mPassword);
    return QDialog::exec();
}





#include "adddevtdialog.h"
#include "ui_adddevtdialog.h"
#include "adddevtsigdlg.h"
#include <qDebug>

#include <QListWidget>

#include <QNetworkReply>
#include <QNetworkRequest>

CAddDevTDialog::CAddDevTDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CAddDevTDialog)
{
    ui->setupUi(this);
}

CAddDevTDialog::~CAddDevTDialog()
{
    delete ui;
}

void CAddDevTDialog::on_pushButton_clicked()
{
    CAddDevTSigDlg dlg;
    dlg.exec();
    qDebug()<<dlg.strDevType;
    qDebug()<<dlg.strDevDes;

    int rCount = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(rCount+1);

    QTableWidgetItem* item1 = new QTableWidgetItem(dlg.strDevType);

    QTableWidgetItem* item2 = new QTableWidgetItem(dlg.strDevDes);

    ui->tableWidget->setItem(rCount, 0, item1);
    //ui->tableWidget->setItemSelected(item1, false);
    ui->tableWidget->setItem(rCount, 1, item2);
    //ui->tableWidget->setItemSelected(item2, false);

}

void CAddDevTDialog::on_pushButton_2_clicked()
{
    QList<DeviceType> devTypes;
    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        DeviceType devType;
        devType.mDevType = ui->tableWidget->item(i,0)->text();
        devType.mDevDes = ui->tableWidget->item(i,1)->text();
        devTypes.append(devType);
    }
    emit signal_addDevType(devTypes);
}

void CAddDevTDialog::on_pushButton_3_clicked()
{
    QList<DeviceType> devTypes;
    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        DeviceType devType;
        devType.mDevType = ui->tableWidget->item(i,0)->text();
        devType.mDevDes = ui->tableWidget->item(i,1)->text();
        devTypes.append(devType);
    }
    emit signal_addDevType(devTypes);
}

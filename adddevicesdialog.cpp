#include "adddevicesdialog.h"
#include "ui_adddevicesdialog.h"

CAddDevicesDialog::CAddDevicesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CAddDevicesDialog)
{
    ui->setupUi(this);
}
void CAddDevicesDialog::initDevType(const QList<DeviceType>& devTypeList)
{
    for(QList<DeviceType>::const_iterator it = devTypeList.begin();
        it != devTypeList.end();
        ++it)
    {
        ui->comboBox->addItem((*it).mDevType);
    }
}
CAddDevicesDialog::~CAddDevicesDialog()
{
    delete ui;
}

void CAddDevicesDialog::on_pushButton_clicked()
{
    strDevType = ui->comboBox->currentText();
    strCount = ui->lineEdit->text();
    strPreName = ui->lineEdit_2->text();
    done(8);
}

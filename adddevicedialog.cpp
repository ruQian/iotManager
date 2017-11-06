#include "adddevicedialog.h"
#include "ui_adddevicedialog.h"

CAddDeviceDialog::CAddDeviceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CAddDeviceDialog)
{
    ui->setupUi(this);
}

CAddDeviceDialog::~CAddDeviceDialog()
{
    delete ui;
}

void CAddDeviceDialog::on_pushButton_clicked()
{
    strDeviceType = ui->comboBox->currentText();
    strDeviceID = ui->lineEdit_2->text();
    done(8);
}
void CAddDeviceDialog::initDevType(const QList<DeviceType>& devTypeList)
{
    for(QList<DeviceType>::const_iterator it = devTypeList.begin();
        it != devTypeList.end();
        ++it)
    {
        ui->comboBox->addItem((*it).mDevType);
    }
}

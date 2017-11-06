#include "adddevtsigdlg.h"
#include "ui_adddevtsigdlg.h"

CAddDevTSigDlg::CAddDevTSigDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CAddDevTSigDlg)
{
    ui->setupUi(this);
}

CAddDevTSigDlg::~CAddDevTSigDlg()
{
    delete ui;
}

void CAddDevTSigDlg::on_pushButton_clicked()
{
    strDevType = ui->lineEdit->text();
    strDevDes = ui->lineEdit_2->text();
    done(1);
}

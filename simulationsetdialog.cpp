#include "simulationsetdialog.h"
#include "ui_simulationsetdialog.h"

CSimulationSetDialog::CSimulationSetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CSimulationSetDialog)
{
    ui->setupUi(this);
}

CSimulationSetDialog::~CSimulationSetDialog()
{
    delete ui;
}

void CSimulationSetDialog::on_pushButton_clicked()
{
    done(8);
}
simulationConfig CSimulationSetDialog::GetConfig()
{
    simulationConfig config;
    config.interval = ui->lineEdit->text().toInt();
    config.strData = ui->textEdit->toPlainText();
    return config;
}

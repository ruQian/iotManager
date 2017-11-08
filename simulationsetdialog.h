#ifndef SIMULATIONSETDIALOG_H
#define SIMULATIONSETDIALOG_H

#include <QDialog>
#include "types.h"
namespace Ui {
class CSimulationSetDialog;
}

class CSimulationSetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CSimulationSetDialog(QWidget *parent = 0);
    ~CSimulationSetDialog();
public:
    simulationConfig GetConfig();
private slots:
    void on_pushButton_clicked();

private:
    Ui::CSimulationSetDialog *ui;
};

#endif // SIMULATIONSETDIALOG_H

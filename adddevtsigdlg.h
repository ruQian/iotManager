#ifndef ADDDEVTSIGDLG_H
#define ADDDEVTSIGDLG_H

#include <QDialog>

namespace Ui {
class CAddDevTSigDlg;
}

class CAddDevTSigDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CAddDevTSigDlg(QWidget *parent = 0);
    ~CAddDevTSigDlg();

private slots:
    void on_pushButton_clicked();
public:
    QString strDevType;
    QString strDevDes;
private:
    Ui::CAddDevTSigDlg *ui;
};

#endif // ADDDEVTSIGDLG_H

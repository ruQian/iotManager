#ifndef WAITWIDGET_H
#define WAITWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QMovie>
namespace Ui {
class CWaitWidget;
}

class CWaitWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CWaitWidget(QWidget *parent = 0);
    ~CWaitWidget();
private:
private slots:
protected:
    virtual void resizeEvent(QResizeEvent *);
    virtual void paintEvent(QPaintEvent *);
private:
    QMovie movie;
    Ui::CWaitWidget *ui;
};

#endif // WAITWIDGET_H

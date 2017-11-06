#ifndef CUSTOMTREEWIDGET_H
#define CUSTOMTREEWIDGET_H
#include <QTreeWidget>

class CCustomTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit CCustomTreeWidget(QWidget *parent = Q_NULLPTR);
    ~CCustomTreeWidget();
Q_SIGNALS:
    void signal_rightPress(QMouseEvent *event);
protected:
    virtual void mousePressEvent(QMouseEvent *event);
};

#endif // CUSTOMTREEWIDGET_H

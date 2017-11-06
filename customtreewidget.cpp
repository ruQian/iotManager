#include "customtreewidget.h"
#include <QMouseEvent>

CCustomTreeWidget::CCustomTreeWidget(QWidget *parent)
    :QTreeWidget(parent)
{

}
CCustomTreeWidget::~CCustomTreeWidget()
{

}
void CCustomTreeWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        emit signal_rightPress(event);
    }
    return QTreeWidget::mousePressEvent(event);
}

#include "waitwidget.h"
#include "ui_waitwidget.h"
#include <QResizeEvent>
#include <QPaintEvent>
#include <QPainter>
CWaitWidget::CWaitWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CWaitWidget)
{
    ui->setupUi(this);
    //QMovie movie(":/image/wait.gif");
    movie.setFileName("D:/wait.gif");
    ui->label->setMovie(&movie);
    movie.start();
    ui->label->show();
}

CWaitWidget::~CWaitWidget()
{
    delete ui;
}

void CWaitWidget::resizeEvent(QResizeEvent* e)
{
    QPixmap image = movie.currentPixmap();
    QSize si(image.width(), image.height());
    QSize si2 = e->size();
    ui->label->resize(si);
    ui->label->move(si2.width()/2-si.width()/2, si2.height()/2-si.height()/2);
}
void CWaitWidget::paintEvent(QPaintEvent *e)
{
    &e;
    QPainter painter(this);
    //this->setAttributte(Qt::WA_TranslucentBackground, true);//关键
    painter.setBrush(QColor(125,125,125,100));
    painter.drawRect(0,0, this->width(), this->height());
}

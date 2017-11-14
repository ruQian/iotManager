#include "mainwindow.h"
#include <QApplication>
#include <QMutex>
#include <QTime>
#include <QFile>
/*
void MessageOutput(QtMsgType type , const QMessageLogContext &context , const QString &msg)
{
    static QMutex mutex;
    mutex.lock();



    QFile logFile("D:\\bluemix.log");
    if(!logFile.open(QFile::Append))
        return ;
    QString log;
    switch(type)
    {
    case QtDebugMsg:
        log = QString("Debug: ");
        break;


    case QtWarningMsg:
        log = QString("Error: ");
        break;


    case QtCriticalMsg:
        log = QString("Critical Error: ");
        break;


    case QtFatalMsg:
        log = QString("Fatal Error: ");
        abort();
        break;


    default:
        log = QString("Unknow Msg Type : ");
        break;
    };


    log += QTime::currentTime().toString("hh:mm:ss.zzz, File: ") + QString(context.file) ;
    log += QString(", Line: " ) + QString::number(context.line) + QString(" : %1\n").arg(msg);
    logFile.write(log.toStdString().c_str());
    logFile.write("\r\n");
    //logFile.flush();
    logFile.close();

    mutex.unlock();
}*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //qInstallMessageHandler(MessageOutput);
    MainWindow w;
    w.show();

    return a.exec();
}

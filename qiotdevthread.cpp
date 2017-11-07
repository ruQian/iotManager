#include "qiotdevthread.h"
#include <QEventLoop>

QAtomicInt g_iotDevCountSu = 0;
QAtomicInt g_iotDevCountFa = 0;

CQIotDevThread::CQIotDevThread(QObject *parent) : QThread(parent)
{
    moveToThread(this);
    client = nullptr;
    connect(&mTimerPub, SIGNAL(timeout()), this, SLOT(slot_timeout()));

    mTimerPub.start(10000);
}

void CQIotDevThread::run()
{
    client = new QMQTT::Client(QHostAddress::LocalHost, 1883);
    if(client != nullptr)
    {

        connect(client, SIGNAL(error(const QMQTT::ClientError)),
                this, SLOT(slot_error(const QMQTT::ClientError)));
        connect(client, SIGNAL(disconnected( )),
                this, SLOT(slot_disconnected( )));


        client->setHostName(strHost);
        client->setPort(port);
        client->setClientId(strClientId);
        client->setUsername(strUsername);
        client->setPassword(strPwd.toUtf8());
        client->setKeepAlive(mAliveTi);

        client->connectToHost();

        QEventLoop eventLoop;
        connect(client, &QMQTT::Client::connected, &eventLoop, &QEventLoop::quit);
        eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
        if(client->isConnectedToHost())
        {
            g_iotDevCountSu++;
            qDebug()<<"连接成功, 成功数量 : "<<g_iotDevCountSu;
        }else{
            g_iotDevCountFa++;
            qDebug()<<"连接失败, 失败数量 : "<<g_iotDevCountFa;
        }


    }
    exec();
}
void CQIotDevThread::slot_timeout()
{
    if(client != nullptr && client->isConnectedToHost())
    {
        QMQTT::Message message;
        message.setTopic("iot-2/evt/status/fmt/json");
        QString str = "{\"tmp\":100}";
        message.setPayload(str.toUtf8());
        client->publish(message);
    }
}
void CQIotDevThread::slot_error(const QMQTT::ClientError error)
{
    qDebug()<<"error : "<<error;
}
void CQIotDevThread::slot_disconnected( )
{
    qDebug()<<"disconnection!"<<strClientId;
}



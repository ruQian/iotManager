#ifndef CQIOTDEVTHREAD_H
#define CQIOTDEVTHREAD_H
#include <QThread>
#include <QTimer>
#include "types.h"
#include "mqtt/qmqtt.h"
class CQIotDevThread : public QThread
{
    Q_OBJECT
public:
    explicit CQIotDevThread(QObject *parent = 0);
public:
    QMQTT::Client *client;


    QString strHost;
    quint16 port;
    quint16 mAliveTi;
    QString strClientId;
    QString strUsername;
    QString strPwd;


    QTimer* mTimerPub;

    simulationConfig mConfig;

    double lat;
    double lon;
protected:
    virtual void run();
signals:

public slots:
    void slot_timeout();
    void slot_error(const QMQTT::ClientError);
    void slot_disconnected();
};

#endif // CQIOTDEVTHREAD_H

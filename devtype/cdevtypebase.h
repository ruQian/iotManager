#ifndef CDEVTYPEBASE_H
#define CDEVTYPEBASE_H

#include <QObject>
/*******
 *设备基类
 */
class CDevTypeBase : public QObject
{
    Q_OBJECT
public:
    explicit CDevTypeBase(QObject *parent = 0);

signals:

public slots:
};

#endif // CDEVTYPEBASE_H

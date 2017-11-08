#ifndef TYPES
#define TYPES
#include <QString>

struct DeviceType
{
    //设备类型
    QString mDevType;
    //设备描述
    QString mDevDes;
};

struct DeviceInfo
{
    //设备类型
    QString mDevType;
    //设备ID
    QString mDevID;
};

struct simulationConfig
{
    //仿真间隔
    int interval;
    //发送数据格式
    QString strData;
    //数据来源
    QString strSource;
};

#endif // TYPES


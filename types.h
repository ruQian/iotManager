#ifndef TYPES
#define TYPES
#include <QString>


struct __deviceInfo{
    //序列号
    QString serialNumber;
    //厂商
    QString manufacturer;
    //
    QString model;
    //设备类
    QString deviceClass;
    //设备描叙
    QString description;
    QString fwVersion;
    QString hwVersion;
    QString descriptiveLocation;
};



struct DeviceType
{
    //设备类型
    QString mDevType;
    //设备描述
    QString mDevDes;
    __deviceInfo info;
    QString classId;
    QString createdDateTime;
    QString updatedDateTime;
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


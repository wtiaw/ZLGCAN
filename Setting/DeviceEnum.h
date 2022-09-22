#ifndef DEVICEENUM_H
#define DEVICEENUM_H

#endif // DEVICEENUM_H

#include "zlgcan.h"
#include <QObject>

class DeviceEnum : public QObject
{
    Q_OBJECT
public:
    enum DEVICEENUM{
        USBCANFD_200U = ZCAN_USBCANFD_200U,
    };
    Q_ENUM(DEVICEENUM)
};

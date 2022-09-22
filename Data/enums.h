#ifndef ENUMS_H
#define ENUMS_H

#include <QObject>
#include "zlgcan.h"

class Enums : public QObject
{
    Q_OBJECT
public:
    explicit Enums(QObject *parent = nullptr);

    enum DEVICEENUM{
        USBCANFD_200U      =   ZCAN_USBCANFD_200U,
    };
    Q_ENUM(DEVICEENUM)

    enum CHANNELNUM{
        Channel0,
        Channel1,
    };
    Q_ENUM(CHANNELNUM)
};

#endif // ENUMS_H

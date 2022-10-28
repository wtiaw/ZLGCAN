#ifndef QRECEIVEITEM_H
#define QRECEIVEITEM_H

#include "typedef.h"
#include "zlgcan.h"
#include <QObject>

struct CANData
{
    ZCAN_Receive_Data can;
    ZCAN_ReceiveFD_Data canfd;
    bool IsCanFD = false;

    CANData(){};

    CANData(ZCAN_Receive_Data& can)
    {
        this->can = can;
        this->IsCanFD = false;
    }
    CANData(ZCAN_ReceiveFD_Data& canfd)
    {
        this->canfd = canfd;
        this->IsCanFD = true;
    }

    CANData(ZCAN_Receive_Data can)
    {
        this->can = can;
        this->IsCanFD = false;
    }
    CANData(ZCAN_ReceiveFD_Data canfd)
    {
        this->canfd = canfd;
        this->IsCanFD = true;
    }

    CANData(CANData const &canfd)
    {
        this->can     = canfd.can;
        this->canfd   = canfd.canfd;
        this->IsCanFD = canfd.IsCanFD;
    }

    CANData(CANData& canfd)
    {
        this->can     = canfd.can;
        this->canfd   = canfd.canfd;
        this->IsCanFD = canfd.IsCanFD;
    }
};

class QReceiveItem : public QObject
{
    Q_OBJECT
public:
    explicit QReceiveItem(QObject *parent = nullptr);

    bool ContaineTrigger(const CANData& Data);

    void ConstructTrigger(uint Id, QVector<BYTE> FilterData, std::function<void (const CANData &)> const Func);

    void On_Trigger(const CANData& Data);

    void SetTrigger(uint Id, QVector<BYTE> FilterData);

signals:
    void Trigger(const CANData& Data);

public slots:
//    void On_Trigger();

private:
    uint FrameId;
    QVector<BYTE> FilterData;
};

#endif // QRECEIVEITEM_H

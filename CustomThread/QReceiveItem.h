#ifndef QRECEIVEITEM_H
#define QRECEIVEITEM_H

#include "typedef.h"
#include "zlgcan.h"
#include <QObject>

struct CANData
{
    canid_t can_id;
    QVector<BYTE> Data;
//    ZCAN_Receive_Data can;
//    ZCAN_ReceiveFD_Data canfd;
//    bool IsCanFD = false;

    CANData() = default;

    CANData(const ZCAN_Receive_Data& can)
    {
        this->can_id = can.frame.can_id;
        for (int i = 0; i < can.frame.can_dlc; ++i) {
            this->Data.append(can.frame.data[i]);
        }
    }
    CANData(const ZCAN_ReceiveFD_Data& canfd)
    {
        this->can_id = canfd.frame.can_id;
        for (int i = 0; i < canfd.frame.len; ++i) {
            this->Data.append(canfd.frame.data[i]);
        }
    }
    CANData(const ZCANCANFDData& Data)
    {
        this->can_id = Data.frame.can_id;
        for (int i = 0; i < Data.frame.len; ++i) {
            this->Data.append(Data.frame.data[i]);
        }
    }

    ~CANData()
    {
        Data.clear();
    }

//    CANData(ZCAN_Receive_Data can)
//    {
//        this->can = can;
//        this->IsCanFD = false;
//    }
//    CANData(ZCAN_ReceiveFD_Data canfd)
//    {
//        this->canfd = canfd;
//        this->IsCanFD = true;
//    }

//    CANData(CANData const &canfd)
//    {
//        this->can     = canfd.can;
//        this->canfd   = canfd.canfd;
//        this->IsCanFD = canfd.IsCanFD;
//    }

//    CANData(CANData& canfd)
//    {
//        this->can     = canfd.can;
//        this->canfd   = canfd.canfd;
//        this->IsCanFD = canfd.IsCanFD;
//    }

//    bool IsValid()
//    {
//        return can.timestamp || canfd.timestamp;
//    }

//    bool operator == (const CANData& c)
//    {
//        if(this->IsCanFD != c.IsCanFD) return false;

//        if(this->IsCanFD)
//        {
//            if(this->canfd.timestamp != c.canfd.timestamp) return false;
//        }
//        else
//        {
//            if(this->can.timestamp != c.can.timestamp) return false;
//        }

//        return true;
//    }

//    bool operator != (const CANData& c)
//    {
//        return !(*this == c);
//    }
};

class QReceiveItem : public QObject
{
    Q_OBJECT
public:
    explicit QReceiveItem(QObject *parent = nullptr);

    bool ContainedTrigger(const CANData& Data);

    void ConstructTrigger(uint Id, QVector<BYTE> FilterData, QObject* context, std::function<void (const CANData &)> const Func);

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

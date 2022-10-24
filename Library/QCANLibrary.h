#ifndef QCANLIBRARY_H
#define QCANLIBRARY_H

#include <QObject>
#include "Data/FromeStruct.h"
#include "zlgcan.h"

struct TableData
{
    UINT64          TimeStamp;
    canid_t         FrameID;
    FrameType       EventType;
    DirectionType   DirType;
    BYTE            DLC;
    QString         Data;
};

class QCANLibrary : public QObject
{
    Q_OBJECT
public:
    explicit QCANLibrary(QObject *parent = nullptr);

    static TableData ConstructTableData(const ZCAN_Transmit_Data& CAN);
    static TableData ConstructTableData(const ZCAN_TransmitFD_Data& CAN);

    static TableData ConstructTableData(const ZCAN_Receive_Data& CAN);
    static TableData ConstructTableData(const ZCAN_ReceiveFD_Data& CANFD);
signals:

};

#endif // QCANLIBRARY_H

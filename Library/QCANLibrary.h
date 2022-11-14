#ifndef QCANLIBRARY_H
#define QCANLIBRARY_H

#include <QObject>
#include "Data/FromeStruct.h"
#include "zlgcan.h"
#include<windows.h>
#include<stdio.h>

struct TableData
{
    LARGE_INTEGER CPUTime;
    UINT64 TimeStamp;
    canid_t FrameID;
    FrameType EventType;
    DirectionType DirType;
    BYTE DLC;
    QVector<BYTE> Data;
    //    QString         Data;
};

//Q_DECLARE_METATYPE(TableData);

class QCANLibrary : public QObject
{
    Q_OBJECT
public:
    explicit QCANLibrary(QObject* parent = nullptr);

    static TableData ConstructTableData(const ZCAN_Transmit_Data& CAN);
    static TableData ConstructTableData(const ZCAN_TransmitFD_Data& CAN);

    static TableData ConstructTableData(const ZCAN_Receive_Data& CAN);
    static TableData ConstructTableData(const ZCAN_ReceiveFD_Data& CANFD);

    //Time
    static LARGE_INTEGER GetCurrentTime_us();
    static double ElapsedTime(const LARGE_INTEGER& StartTime, const LARGE_INTEGER& EndTime);
signals:
};

#endif // QCANLIBRARY_H

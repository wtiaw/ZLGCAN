#include "QCANLibrary.h"

QCANLibrary::QCANLibrary(QObject* parent)
    : QObject{parent}
{
}

TableData QCANLibrary::ConstructTableData(const ZCAN_Transmit_Data& CAN)
{
    const canid_t& id = CAN.frame.can_id;
    //    QString str;

    TableData InTableData;
    InTableData.TimeStamp = 0;
    InTableData.CPUTime = GetCurrentTime_us();
    InTableData.FrameID = GET_ID(id);
    InTableData.EventType = FrameType::CAN;
    InTableData.DirType = DirectionType::Transmit;
    InTableData.DLC = CAN.frame.can_dlc;

    for (UINT i = 0; i < CAN.frame.can_dlc; ++i)
    {
        InTableData.Data.append(CAN.frame.data[i]);
    }

    return InTableData;
}

TableData QCANLibrary::ConstructTableData(const ZCAN_TransmitFD_Data& CAN)
{
    const canid_t& id = CAN.frame.can_id;
    QString str;

    TableData InTableData;
    InTableData.TimeStamp = 0;
    InTableData.CPUTime = GetCurrentTime_us();
    InTableData.FrameID = GET_ID(id);
    InTableData.EventType = FrameType::CANFD;
    InTableData.DirType = DirectionType::Transmit;
    InTableData.DLC = CAN.frame.len;

    for (UINT i = 0; i < CAN.frame.len; ++i)
    {
        InTableData.Data.append(CAN.frame.data[i]);
    }

    return InTableData;
}

TableData QCANLibrary::ConstructTableData(const ZCAN_Receive_Data& CAN)
{
    const canid_t& id = CAN.frame.can_id;
    QString str;

    TableData InTableData;
    InTableData.TimeStamp = CAN.timestamp;
    InTableData.CPUTime = GetCurrentTime_us();
    InTableData.FrameID = GET_ID(id);
    InTableData.EventType = FrameType::CAN;
    InTableData.DirType = DirectionType::Receive;
    InTableData.DLC = CAN.frame.can_dlc;

    for (UINT i = 0; i < CAN.frame.can_dlc; ++i)
    {
        InTableData.Data.append(CAN.frame.data[i]);
    }

    return InTableData;
}

TableData QCANLibrary::ConstructTableData(const ZCAN_ReceiveFD_Data& CANFD)
{
    const canid_t& id = CANFD.frame.can_id;
    QString str;

    TableData InTableData;
    InTableData.TimeStamp = CANFD.timestamp;
    InTableData.CPUTime = GetCurrentTime_us();
    InTableData.FrameID = GET_ID(id);
    InTableData.EventType = FrameType::CANFD;
    InTableData.DirType = DirectionType::Receive;
    InTableData.DLC = CANFD.frame.len;

    for (UINT i = 0; i < CANFD.frame.len; ++i)
    {
        InTableData.Data.append(CANFD.frame.data[i]);
    }

    return InTableData;
}

LARGE_INTEGER QCANLibrary::GetCurrentTime_us()
{
    LARGE_INTEGER t1;
    QueryPerformanceCounter(&t1);

    return t1;
}

double QCANLibrary::ElapsedTime(const LARGE_INTEGER& StartTime, const LARGE_INTEGER& EndTime)
{
    LARGE_INTEGER nFreq;
    QueryPerformanceFrequency(&nFreq);
    return (EndTime.QuadPart - StartTime.QuadPart) / static_cast<double>(nFreq.QuadPart);
}

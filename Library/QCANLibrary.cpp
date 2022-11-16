#include "QCANLibrary.h"

QCANLibrary::QCANLibrary(QObject* parent)
    : QObject{parent}
{
}

TableData QCANLibrary::ConstructTableData(const ZCANDataObj& CANDataObj)
{
    const auto [timeStamp, flag, extraData, frame] = CANDataObj.data.zcanCANFDData;
    const canid_t& id = frame.can_id;

    TableData InTableData;
    InTableData.TimeStamp = timeStamp;
    InTableData.FrameID = GET_ID(id);
    InTableData.EventType = flag.unionVal.frameType == 0 ? FrameType::CAN : FrameType::CANFD;
    InTableData.DirType = flag.unionVal.txEchoed == 0 ? DirectionType::Receive : DirectionType::Transmit;
    InTableData.DLC = frame.len;

    for (UINT i = 0; i < frame.len; ++i)
    {
        InTableData.Data.append(frame.data[i]);
    }

    return InTableData;
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

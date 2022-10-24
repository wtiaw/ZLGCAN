#include "QCANLibrary.h"
#include "qdatetime.h"

QCANLibrary::QCANLibrary(QObject *parent)
    : QObject{parent}
{

}

TableData QCANLibrary::ConstructTableData(const ZCAN_Transmit_Data &CAN)
{
    const canid_t& id = CAN.frame.can_id;
    QString str;

    TableData InTableData;
    InTableData.TimeStamp    =   QDateTime::currentMSecsSinceEpoch();
    InTableData.FrameID      =   GET_ID(id);
    InTableData.EventType    =   FrameType::CAN;
    InTableData.DirType      =   DirectionType::Transmit;
    InTableData.DLC          =   CAN.frame.can_dlc;

    for (UINT i = 0; i < CAN.frame.can_dlc; ++i)
    {

        str += QString("%1 ").arg(CAN.frame.data[i], 2, 16, QLatin1Char('0'));
    }

    InTableData.Data = str.toUpper();

    return InTableData;
}

TableData QCANLibrary::ConstructTableData(const ZCAN_TransmitFD_Data &CAN)
{
    const canid_t& id = CAN.frame.can_id;
    QString str;

    TableData InTableData;
    InTableData.TimeStamp    =   QDateTime::currentMSecsSinceEpoch();
    InTableData.FrameID      =   GET_ID(id);
    InTableData.EventType    =   FrameType::CANFD;
    InTableData.DirType      =   DirectionType::Transmit;
    InTableData.DLC          =   CAN.frame.len;

    for (UINT i = 0; i < CAN.frame.len; ++i)
    {

        str += QString("%1 ").arg(CAN.frame.data[i], 2, 16, QLatin1Char('0'));
    }

    InTableData.Data = str.toUpper();

    return InTableData;
}

TableData QCANLibrary::ConstructTableData(const ZCAN_Receive_Data &CAN)
{
    const canid_t& id = CAN.frame.can_id;
    QString str;

    TableData InTableData;
    InTableData.TimeStamp    =   CAN.timestamp;
    InTableData.FrameID      =   GET_ID(id);
    InTableData.EventType    =   FrameType::CAN;
    InTableData.DirType      =   DirectionType::Receive;
    InTableData.DLC          =   CAN.frame.can_dlc;

    for (UINT i = 0; i < CAN.frame.can_dlc; ++i)
    {

        str += QString("%1 ").arg(CAN.frame.data[i], 2, 16, QLatin1Char('0'));
    }

    InTableData.Data = str.toUpper();

    return InTableData;
}

TableData QCANLibrary::ConstructTableData(const ZCAN_ReceiveFD_Data &CANFD)
{
    const canid_t& id = CANFD.frame.can_id;
    QString str;

    TableData InTableData;
    InTableData.TimeStamp    =   CANFD.timestamp;
    InTableData.FrameID      =   GET_ID(id);
    InTableData.EventType    =   FrameType::CANFD;
    InTableData.DirType      =   DirectionType::Receive;
    InTableData.DLC          =   CANFD.frame.len;

    for (UINT i = 0; i < CANFD.frame.len; ++i)
    {

        str += QString("%1 ").arg(CANFD.frame.data[i], 2, 16, QLatin1Char('0'));
    }

    InTableData.Data = str.toUpper();

    return InTableData;
}

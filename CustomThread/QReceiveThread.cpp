#include "QReceiveThread.h"
#include "qdebug.h"
#include <QMetaType>

QReceiveThread::QReceiveThread(QObject *parent)
    : QThreadBase{parent}
{
    mainWindow = qobject_cast<MainWindow*>(parent);

    ReceiveItemContainer.clear();
//    qRegisterMetaType<TableData>("TableData");
//    qRegisterMetaType<ZCAN_Transmit_Data>("ZCAN_Transmit_Data");
//    qRegisterMetaType<ZCAN_TransmitFD_Data>("ZCAN_TransmitFD_Data");
}

QReceiveThread::~QReceiveThread()
{
    Stop();
}

void QReceiveThread::run()
{
    QThreadBase::run();

    bIsPause = false;

    connect(this, SIGNAL(AddTableData(const TableData&)), mainWindow, SLOT(AddTableData(const TableData&)));
    connect(this, SIGNAL(AddCANTableData_T(const ZCAN_Transmit_Data&)), mainWindow, SLOT(AddTableData(const ZCAN_Transmit_Data&)));
    connect(this, SIGNAL(AddCANFDTableData_T(const ZCAN_TransmitFD_Data&)), mainWindow, SLOT(AddTableData(const ZCAN_TransmitFD_Data&)));
    connect(this, SIGNAL(AddCANTableData_R(const ZCAN_Receive_Data&)), mainWindow, SLOT(AddTableData(const ZCAN_Receive_Data&)));
    connect(this, SIGNAL(AddCANFDTableData_R(const ZCAN_ReceiveFD_Data&)), mainWindow, SLOT(AddTableData(const ZCAN_ReceiveFD_Data&)));

    CHANNEL_HANDLE chHandle = mainWindow->GetChannelHandle();

    while(!isInterruptionRequested()){
        if(!bIsPause){
            ReceiveData(chHandle);
        }
        usleep(100);
    }
}

void QReceiveThread::Stop()
{
    disconnect(this, 0, mainWindow, 0);
    QThreadBase::Stop();
}

void QReceiveThread::AddTrigger(uint Id, QVector<BYTE>& FilterData)
{
    QReceiveItem* Item = new QReceiveItem;
    Item->SetTrigger(Id, FilterData);

    AddTrigger(Item);
}

void QReceiveThread::AddTrigger(QReceiveItem *NewItem)
{
    ReceiveItemContainer.append(NewItem);
}

void QReceiveThread::AddTrigger(QVector<QReceiveItem *> NewItems)
{
    ReceiveItemContainer.append(NewItems);
}

void QReceiveThread::ReceiveData(CHANNEL_HANDLE& ChannelHandle)
{
    ZCAN_Receive_Data can_data[100];
    ZCAN_ReceiveFD_Data canfd_data[100];
    UINT len;

    if (len = ZCAN_GetReceiveNum(ChannelHandle, TYPE_CAN))
    {
        len = ZCAN_Receive(ChannelHandle, can_data, 100);

        for (UINT i = 0; i < len; ++i)
        {
            const ZCAN_Receive_Data& can = can_data[i];

            emit AddCANTableData_R(can);
            Reception(can);
        }
    }

    if (len = ZCAN_GetReceiveNum(ChannelHandle, TYPE_CANFD))
    {
        len = ZCAN_ReceiveFD(ChannelHandle, canfd_data, 100);

        for (UINT i = 0; i < len; ++i)
        {
            const ZCAN_ReceiveFD_Data& canfd = canfd_data[i];

            emit AddCANFDTableData_R(canfd);
            Reception(canfd);
        }
    }
}

void QReceiveThread::Reception(const CANData &Data)
{
    for (auto i : ReceiveItemContainer) {
        if(i->ContaineTrigger(Data))
            i->On_Trigger(Data);
    }
}

//void QReceiveThread::InitReceptionData(CHANNEL_HANDLE& ChannelHandle)
//{
//    ReceptionDatas.clear();
//    QVector<BYTE> Temp = {0x07, 0x62};
//    AddReceptionData(0x748, Temp, [&](ZCAN_ReceiveFD_Data&) -> void
//    {
//        ZCAN_TransmitFD_Data can_data;

//        memset(&can_data, 0, sizeof(can_data));
//        can_data.frame.can_id   =  MAKE_CAN_ID(0x740, 0, 0, 0);         // CAN ID
//        can_data.frame.len      =  8;                                 // CAN 数据长度
//        can_data.transmit_type  =  0;
//        can_data.frame.data[0] = 0x03;
//        can_data.frame.data[1] = 0x22;
//        can_data.frame.data[2] = 0xFD;
//        can_data.frame.data[3] = 0x07;

//        ZCAN_TransmitFD(ChannelHandle, &can_data, 1);

//        emit AddCANFDTableData_T(can_data);
//    });

//    Temp = {0x10, 0x21};
//    AddReceptionData(0x748, Temp, [=]() -> void
//    {
//        ZCAN_TransmitFD_Data can_data;

//        memset(&can_data, 0, sizeof(can_data));
//        can_data.frame.can_id   =  MAKE_CAN_ID(0x740, 0, 0, 0);         // CAN ID
//        can_data.frame.len      =  8;                                 // CAN 数据长度
//        can_data.transmit_type  =  0;
//        can_data.frame.data[0] = 0x30;

//        ZCAN_TransmitFD(ChannelHandle, &can_data, 1);

//        emit AddCANFDTableData_T(can_data);
//    });

//    Temp = {0x06, 0x67, 0x61};
//    AddReceptionData(0x748, Temp, [=]() -> void
//    {
//        ZCAN_TransmitFD_Data can_data;

//        memset(&can_data, 0, sizeof(can_data));
//        can_data.frame.can_id   =  MAKE_CAN_ID(0x740, 0, 0, 0);         // CAN ID
//        can_data.frame.len      =  8;                                 // CAN 数据长度
//        can_data.transmit_type  =  0;
//        can_data.frame.data[0] = 0x30;

//        ZCAN_TransmitFD(ChannelHandle, &can_data, 1);

//        emit AddCANFDTableData_T(can_data);
//    });
//}

//bool QReceiveThread::ShouldReception(const ZCAN_Receive_Data &Data, const ReceptionData<ZCAN_Receive_Data> InReceptionData)
//{
//    if(Data.frame.can_id != InReceptionData.FrameId) return false;
//    for(int i = 0 ; i < InReceptionData.FilterData.length() ; i++)
//    {
//        if(Data.frame.data[i] != InReceptionData.FilterData[i]) return false;
//    }

//    return true;
//}

//bool QReceiveThread::ShouldReception(const ZCAN_ReceiveFD_Data &Data, const ReceptionData<ZCAN_ReceiveFD_Data> InReceptionData)
//{
//    if(Data.frame.can_id != InReceptionData.FrameId) return false;
//    for(int i = 0 ; i < InReceptionData.FilterData.length() ; i++)
//    {
//        if(Data.frame.data[i] != InReceptionData.FilterData[i]) return false;
//    }

//    return true;
//}

//void QReceiveThread::Reception(const ZCAN_Receive_Data& Data)
//{
//    for(auto& i : ReceptionDatas)
//    {
//        if(ShouldReception(Data,i))
//        {
//            if(i.FuncNoMember)
//                i.FuncNoMember();

//            if(i.FuncMember)
//                (this->*i.FuncMember)();

//            return;
//        }
//    }
//}

//void QReceiveThread::Reception(const ZCAN_ReceiveFD_Data& Data)
//{
//    for(auto& i : ReceptionDatas)
//    {
//        if(ShouldReception(Data,i))
//        {
//            if(i.FuncNoMember)
//                i.FuncNoMember();

//            if(i.FuncMember)
//                (this->*i.FuncMember)();

//            return;
//        }
//    }
//}

void QReceiveThread::Test()
{
    qDebug() << "经过时间:" << ElapsedTimer->elapsed();
}

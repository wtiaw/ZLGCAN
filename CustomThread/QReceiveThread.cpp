#include "QReceiveThread.h"
#include "qdebug.h"

QReceiveThread::QReceiveThread(QObject *parent)
    : QThreadBase{parent}
{
    mainWindow = qobject_cast<MainWindow*>(parent);
}

QReceiveThread::~QReceiveThread()
{
    Stop();
}

void QReceiveThread::run()
{
    qDebug() << "当前子线程ID:" << QThread::currentThreadId();
    qDebug() << "开始执行线程";

    bIsPause = false;

    connect(this, SIGNAL(AddTableData(const TableData&)), mainWindow, SLOT(AddTableData(const TableData&)));
    CHANNEL_HANDLE chHandle = mainWindow->GetChannelHandle();
    InitReceptionData(chHandle);

    while(!isInterruptionRequested()){
        if(!bIsPause){
            ReceiveData(chHandle);
        }
        usleep(100);
    }
}

void QReceiveThread::ReceiveData(CHANNEL_HANDLE ChannelHandle)
{
    ZCAN_Receive_Data can_data[100];
    ZCAN_ReceiveFD_Data canfd_data[100];
    UINT len;

    if (len = ZCAN_GetReceiveNum(ChannelHandle, TYPE_CAN))
    {
        len = ZCAN_Receive(ChannelHandle, can_data, 100, 1);

        for (UINT i = 0; i < len; ++i)
        {
            const ZCAN_Receive_Data& can = can_data[i];

            emit AddTableData(QCANLibrary::ConstructTableData(can));
            Reception(can);
        }
    }

    if (len = ZCAN_GetReceiveNum(ChannelHandle, TYPE_CANFD))
    {
        len = ZCAN_ReceiveFD(ChannelHandle, canfd_data, 100, 1);

        for (UINT i = 0; i < len; ++i)
        {
            const ZCAN_ReceiveFD_Data& canfd = canfd_data[i];
Reception(canfd);
            emit AddTableData(QCANLibrary::ConstructTableData(canfd));

        }
    }
}

void QReceiveThread::InitReceptionData(CHANNEL_HANDLE ChannelHandle)
{
    ReceptionDatas.clear();
    QVector<BYTE> Temp = {0x07, 0x62};
    AddReceptionData(0x748, Temp, [=]() -> void
    {
        ZCAN_TransmitFD_Data can_data;

        memset(&can_data, 0, sizeof(can_data));
        can_data.frame.can_id   =  MAKE_CAN_ID(0x740, 0, 0, 0);         // CAN ID
        can_data.frame.len      =  8;                                 // CAN 数据长度
        can_data.transmit_type  =  0;
        can_data.frame.data[0] = 0x03;
        can_data.frame.data[1] = 0x22;
        can_data.frame.data[2] = 0xFD;
        can_data.frame.data[3] = 0x07;

        ZCAN_TransmitFD(ChannelHandle, &can_data, 1);
        emit AddTableData(QCANLibrary::ConstructTableData(can_data));
    });

    Temp = {0x10, 0x21};
    AddReceptionData(0x748, Temp, [=]() -> void
    {
        ZCAN_TransmitFD_Data can_data;

        memset(&can_data, 0, sizeof(can_data));
        can_data.frame.can_id   =  MAKE_CAN_ID(0x740, 0, 0, 0);         // CAN ID
        can_data.frame.len      =  8;                                 // CAN 数据长度
        can_data.transmit_type  =  0;
        can_data.frame.data[0] = 0x30;

        ZCAN_TransmitFD(ChannelHandle, &can_data, 1);
        emit AddTableData(QCANLibrary::ConstructTableData(can_data));
    });
}

void QReceiveThread::AddReceptionData(const uint FrameID, const QVector<BYTE> FilterData, const std::function<void ()> Func)
{
    ReceptionData Temp;

    Temp.FrameId = FrameID;
    Temp.FilterData = FilterData;
    Temp.FuncNoMember = Func;

    ReceptionDatas.append(Temp);
}

bool QReceiveThread::ShouldReception(const ZCAN_Receive_Data &Data, const ReceptionData InReceptionData)
{
    if(Data.frame.can_id != InReceptionData.FrameId) return false;
    for(int i = 0 ; i < InReceptionData.FilterData.length() ; i++)
    {
        if(Data.frame.data[i] != InReceptionData.FilterData[i]) return false;
    }

    return true;
}

bool QReceiveThread::ShouldReception(const ZCAN_ReceiveFD_Data &Data, const ReceptionData InReceptionData)
{
    if(Data.frame.can_id != InReceptionData.FrameId) return false;
    for(int i = 0 ; i < InReceptionData.FilterData.length() ; i++)
    {
        if(Data.frame.data[i] != InReceptionData.FilterData[i]) return false;
    }

    return true;
}

void QReceiveThread::Reception(const ZCAN_Receive_Data& Data)
{
    for(auto& i : ReceptionDatas)
    {
        if(ShouldReception(Data,i))
        {
            if(i.FuncNoMember)
                i.FuncNoMember();

            if(i.FuncMember)
                (this->*i.FuncMember)();

            return;
        }
    }
}

void QReceiveThread::Reception(const ZCAN_ReceiveFD_Data& Data)
{
    for(auto& i : ReceptionDatas)
    {
        if(ShouldReception(Data,i))
        {
            if(i.FuncNoMember)
                i.FuncNoMember();

            if(i.FuncMember)
                (this->*i.FuncMember)();

            return;
        }
    }
}

void QReceiveThread::Test()
{
    qDebug() << "经过时间:" << ElapsedTimer->elapsed();
}

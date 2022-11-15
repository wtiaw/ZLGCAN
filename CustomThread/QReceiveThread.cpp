#include "QReceiveThread.h"
#include "qdebug.h"
#include <QMetaType>

QReceiveThread::QReceiveThread(QObject* parent)
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

    connect(this, SIGNAL(AddCANTableData_R(const ZCAN_Receive_Data&)), mainWindow,
            SLOT(AddTableData(const ZCAN_Receive_Data&)));
    connect(this, SIGNAL(AddCANFDTableData_R(const ZCAN_ReceiveFD_Data&)), mainWindow,
            SLOT(AddTableData(const ZCAN_ReceiveFD_Data&)));
    connect(this, SIGNAL(TransmitCAN(ZCAN_Transmit_Data&)), mainWindow, SLOT(TransmitCANData(ZCAN_Transmit_Data&)));
    connect(this, SIGNAL(TransmitCANFD(ZCAN_TransmitFD_Data&)), mainWindow,
            SLOT(TransmitCANData(ZCAN_TransmitFD_Data&)));

    CHANNEL_HANDLE chHandle = mainWindow->GetChannelHandle();

    while (!isInterruptionRequested())
    {
        if (!bIsPause)
        {
            ReceiveData(chHandle);
        }
        usleep(100);
    }
}

void QReceiveThread::Stop()
{
    disconnect(this, nullptr, mainWindow, nullptr);
    QThreadBase::Stop();
}

void QReceiveThread::AddTrigger(const uint Id, const QVector<BYTE>& FilterData)
{
    auto* Item = new QReceiveItem;
    Item->SetTrigger(Id, FilterData);

    AddTrigger(Item);
}

void QReceiveThread::AddTrigger(QReceiveItem* NewItem)
{
    ReceiveItemContainer.append(NewItem);
}

void QReceiveThread::AddTrigger(const QVector<QReceiveItem*>& NewItems)
{
    ReceiveItemContainer.append(NewItems);
}

void QReceiveThread::ReceiveData(const CHANNEL_HANDLE& ChannelHandle)
{
    UINT len;

    if (len = ZCAN_GetReceiveNum(ChannelHandle, TYPE_CAN))
    {
        ZCAN_Receive_Data can_data[10];
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
        ZCAN_ReceiveFD_Data canfd_data[10];
        len = ZCAN_ReceiveFD(ChannelHandle, canfd_data, 100);

        for (UINT i = 0; i < len; ++i)
        {
            const ZCAN_ReceiveFD_Data& canfd = canfd_data[i];

            emit AddCANFDTableData_R(canfd);
            Reception(canfd);
        }
    }
}

void QReceiveThread::Reception(const CANData& Data)
{
    if (mainWindow->temp == 0)
        mainWindow->temp = QCANLibrary::ElapsedTime(mainWindow->TStartTime, QCANLibrary::GetCurrentTime_us()) * 1000000;

    if (const BYTE Single = Data.Data[0] >> 4; Single == 1)
    {
        FirstFrameId = Data.can_id;
        length = Data.Data[1];

        ZCAN_TransmitFD_Data can_data = {};

        can_data.frame.can_id = MAKE_CAN_ID(0x740, 0, 0, 0); // CAN ID
        can_data.frame.len = 8; // CAN 数据长度
        can_data.transmit_type = 0;
        can_data.frame.data[0] = 0x30;

        emit TransmitCANFD(can_data);
        //        mainWindow->TransmitCANData(can_data);

        for (int i = 0; i < 6; i++)
        {
            canData.append(Data.Data[i + 2]);
            length--;
        }
    }
    else if (Single == 2)
    {
        for (int i = 0; i < 7; i++)
        {
            canData.append(Data.Data[i + 1]);
            length--;

            if (length == 0)
            {
                CANData can;
                can.can_id = FirstFrameId;
                can.Data = canData;

                for (auto i : ReceiveItemContainer)
                {
                    if (i->ContainedTrigger(can))
                        i->On_Trigger(can);
                }

                canData.clear();
                break;
            }
        }
    }
    else if (Single == 0)
    {
        for (const auto i : ReceiveItemContainer)
        {
            if (i->ContainedTrigger(Data))
                i->On_Trigger(Data);
        }
    }
}

void QReceiveThread::Test() const
{
    qDebug() << "经过时间:" << ElapsedTimer->elapsed();
}

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

    connect(this, SIGNAL(AddCANTableData(const ZCANDataObj&)), mainWindow,
            SLOT(AddTableData(const ZCANDataObj&)));

    // connect(this, SIGNAL(TransmitCAN(ZCAN_Transmit_Data&)), mainWindow, SLOT(TransmitCANData(ZCAN_Transmit_Data&)));
    connect(this, SIGNAL(TransmitCANFD(ZCAN_TransmitFD_Data&)), mainWindow,
            SLOT(TransmitCANDataObj(ZCAN_TransmitFD_Data&)));

    const CHANNEL_HANDLE chHandle = mainWindow->GetChannelHandle();

    while (!isInterruptionRequested())
    {
        if (!bIsPause)
        {
            ReceiveData(chHandle);
        }
        usleep(1000);
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

void QReceiveThread::ClearTrigger()
{
    ReceiveItemContainer.clear();
}

int QReceiveThread::GetTriggerCount()
{
    return ReceiveItemContainer.size();
}

void QReceiveThread::ReceiveData(const CHANNEL_HANDLE& ChannelHandle)
{
    if(UINT len = ZCAN_GetReceiveNum(ChannelHandle, TYPE_ALL_DATA))
    {
        ZCANDataObj DataObj[100];

        len = ZCAN_ReceiveData(ChannelHandle, DataObj, 100);

        for (UINT i = 0; i < len; ++i)
        {
            switch (DataObj[i].dataType)
            {
            case ZCAN_DT_ZCAN_CAN_CANFD_DATA:
                {
                    if (mainWindow->StartTime == 0)
                    {
                        mainWindow->StartTime = DataObj[i].data.zcanCANFDData.timeStamp;
                    }
                    
                    const ZCANCANFDData CANFDData = DataObj[i].data.zcanCANFDData;

                    emit AddCANTableData(DataObj[i]);
                    Reception(CANFDData);

                    break;
                }
            case ZCAN_DT_ZCAN_ERROR_DATA:
                if (mainWindow->StartTime == 0)
                {
                    mainWindow->StartTime = DataObj[i].data.zcanErrData.timeStamp;
                }

                const ZCANErrorData CANErrData = DataObj[i].data.zcanErrData;

                switch (CANErrData.errType)
                {
                case ZCAN_ERR_TYPE_NO_ERR:
                    qDebug() << "errType: ?????????";
                    break;
                case ZCAN_ERR_TYPE_BUS_ERR:
                    qDebug() << "errType: ????????????";
                    break;
                case ZCAN_ERR_TYPE_CONTROLLER_ERR:
                    qDebug() << "errType: ???????????????";
                    break;
                case ZCAN_ERR_TYPE_DEVICE_ERR:
                    qDebug() << "errType: ??????????????????";
                    break;
                }

                switch (CANErrData.errSubType)
                {
                case ZCAN_BUS_ERR_NO_ERR:
                    qDebug() << "errSubType ?????????";
                    break;
                case ZCAN_BUS_ERR_BIT_ERR:
                    qDebug() << "errSubType ?????????";
                    break;
                case ZCAN_BUS_ERR_ACK_ERR:
                    qDebug() << "errSubType ????????????";
                    break;
                case ZCAN_BUS_ERR_CRC_ERR:
                    qDebug() << "errSubType CRC??????";
                    break;
                case ZCAN_BUS_ERR_FORM_ERR:
                    qDebug() << "errSubType ????????????";
                    break;
                case ZCAN_BUS_ERR_STUFF_ERR:
                    qDebug() << "errSubType ????????????";
                    break;
                case ZCAN_BUS_ERR_OVERLOAD_ERR:
                    qDebug() << "errSubType ????????????";
                    break;
                case ZCAN_BUS_ERR_ARBITRATION_LOST:
                    qDebug() << "errSubType ????????????";
                    break;
                }

                break;
            }
        }
    }
}

void QReceiveThread::Reception(const ZCANCANFDData& Data)
{
    if (const BYTE Single = Data.frame.data[0] >> 4; Single == 1)
    {
        FirstFrameId = Data.frame.can_id;
        length = Data.frame.data[1];

        ZCAN_TransmitFD_Data can_data = {};

        can_data.frame.can_id = MAKE_CAN_ID(0x740, 0, 0, 0); // CAN ID
        can_data.frame.len = 8; // CAN ????????????
        can_data.transmit_type = 0;
        can_data.frame.data[0] = 0x30;

        emit TransmitCANFD(can_data);

        for (int i = 0; i < 6; i++)
        {
            canData.append(Data.frame.data[i + 2]);
            length--;
        }
    }
    else if (Single == 2)
    {
        for (int i = 0; i < 7; i++)
        {
            canData.append(Data.frame.data[i + 1]);
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
    qDebug() << "????????????:" << ElapsedTimer->elapsed();
}

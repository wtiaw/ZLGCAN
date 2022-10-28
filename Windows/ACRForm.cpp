#include "ACRForm.h"
#include "CustomThread/QReceiveItem.h"
#include "mainwindow.h"
#include <QByteArray>
#include <QtConcurrent>
#include "ui_ACRForm.h"
#include "zlgcan.h"
#include "CustomThread/QReceiveThread.h"

ACRForm::ACRForm(QWidget *parent, Qt::WindowFlags f) :
    QWidget(parent, f),
    ui(new Ui::ACRForm)
{
    setAttribute(Qt::WA_QuitOnClose, false);

    ui->setupUi(this);

    setWindowTitle(QString("ACR"));

    mainWindow = qobject_cast<MainWindow*>(parent);
    InitTrigger();

    memset(&canfd_data_406, 0, sizeof(canfd_data_406));
    canfd_data_406.frame.can_id    =  MAKE_CAN_ID(0x406, 0, 0, 0);
    canfd_data_406.frame.len       =  8;
    canfd_data_406.transmit_type   =  0;

    memset(&canfd_data_121, 0, sizeof(canfd_data_121));
    canfd_data_121.frame.can_id    =  MAKE_CAN_ID(0x121, 0, 0, 0);
    canfd_data_121.frame.len       =  8;
    canfd_data_121.transmit_type   =  0;
    canfd_data_121.frame.data[1]   =  0x20;

    memset(&canfd_data_1C2, 0, sizeof(canfd_data_1C2));
    canfd_data_1C2.frame.can_id    =  MAKE_CAN_ID(0x1C2, 0, 0, 0);
    canfd_data_1C2.frame.len       =  64;
    canfd_data_1C2.transmit_type   =  0;
    canfd_data_1C2.frame.data[12]  =  0x01;
    canfd_data_1C2.frame.data[16]  =  0x04;

    memset(&canfd_data_50, 0, sizeof(canfd_data_50));
    canfd_data_50.frame.can_id     =  MAKE_CAN_ID(0x50, 0, 0, 0);
    canfd_data_50.frame.len        =  8;
    canfd_data_50.transmit_type    =  0;

    memset(&canfd_data_288, 0, sizeof(canfd_data_288));
    canfd_data_288.frame.can_id    =  MAKE_CAN_ID(0x288, 0, 0, 0);
    canfd_data_288.frame.len       =  8;
    canfd_data_288.transmit_type   =  0;
    canfd_data_288.frame.data[5]   =  0x08;

    memset(&canfd_data_2D2, 0, sizeof(canfd_data_2D2));
    canfd_data_2D2.frame.can_id    =  MAKE_CAN_ID(0x2D2, 0, 0, 0);
    canfd_data_2D2.frame.len       =  64;
    canfd_data_2D2.transmit_type   =  0;

    memset(&canfd_data_2F7, 0, sizeof(canfd_data_2F7));
    canfd_data_2F7.frame.can_id    =  MAKE_CAN_ID(0x2F7, 0, 0, 0);
    canfd_data_2F7.frame.len       =  64;
    canfd_data_2F7.transmit_type   =  0;
}

ACRForm::~ACRForm()
{
    delete ui;
}

void ACRForm::TransmitMessageByTimer(EMessageTimer InMessageTimerType, ZCAN_Transmit_Data *CANData, void (ACRForm::*Function)(), uint delay, uint msec)
{
    TransmitMessageByTimer<ZCAN_Transmit_Data>(InMessageTimerType, CANData, Function, delay, msec);
}

void ACRForm::TransmitMessageByTimer(EMessageTimer InMessageTimerType, ZCAN_TransmitFD_Data *CANData, void (ACRForm::*Function)(), uint delay, uint msec)
{
    TransmitMessageByTimer<ZCAN_TransmitFD_Data>(InMessageTimerType, CANData, Function, delay, msec);
}

void ACRForm::TransmitMessageByTimer(EMessageTimer InMessageTimerType, ZCAN_TransmitFD_Data &CANData, void (ACRForm::*Function)(), uint delay, uint msec)
{
    if(!cHandle)
        cHandle = mainWindow->GetChannelHandle();

    PerformanceFrequency* temp;

    if(!MessageThreadContainer.contains(InMessageTimerType))
    {
        temp = new PerformanceFrequency;

        connect(temp, &PerformanceFrequency::TimeOut, this, [=]() mutable -> void
        {
            mainWindow->TransmitCANData(CANData);

            if(Function)
                (this->*Function)();
        }, Qt::QueuedConnection);

        if(InMessageTimerType != EMessageTimer::Single)
            MessageThreadContainer.insert(InMessageTimerType, temp);
    }
    else
    {
        temp = MessageThreadContainer[InMessageTimerType];
    }

    temp->setThreadRunning(delay, msec, InMessageTimerType == EMessageTimer::Single);
}

void ACRForm::StopTimer()
{
    for(auto i : MessageThreadContainer.values())
    {
        i->setThreadStop();
    }

    for(auto& i : MessageTimerContainer.values())
    {
        i->stop();
    }
}

void ACRForm::InitTrigger()
{
    auto ReceiveThread = mainWindow->ReceiveThread;

    QVector<BYTE> Temp = {0x07, 0x62};
    CreateItem(0x748, Temp, [&](const CANData& Data)
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

        mainWindow->TransmitCANData(can_data);
    });

    Temp = {0x10, 0x21};
    CreateItem(0x748, Temp, [&](const CANData& Data)
    {
        ZCAN_TransmitFD_Data can_data;

        memset(&can_data, 0, sizeof(can_data));
        can_data.frame.can_id   =  MAKE_CAN_ID(0x740, 0, 0, 0);         // CAN ID
        can_data.frame.len      =  8;                                 // CAN 数据长度
        can_data.transmit_type  =  0;
        can_data.frame.data[0] = 0x30;

        mainWindow->TransmitCANData(can_data);
    });

    Temp = {0x06, 0x67, 0x61};
    CreateItem(0x748, Temp, [&](const CANData& Data)
    {
        ZCAN_TransmitFD_Data can_data;

        memset(&can_data, 0, sizeof(can_data));
        can_data.frame.can_id   =  MAKE_CAN_ID(0x740, 0, 0, 0);         // CAN ID
        can_data.frame.len      =  8;                                 // CAN 数据长度
        can_data.transmit_type  =  0;
        can_data.frame.data[0] = 0x30;

        mainWindow->TransmitCANData(can_data);
    });

    ReceiveThread->AddTrigger(Items);
    qDebug()<<"init";
}

BYTE ACRForm::can_e2e_CalculateCRC8(BYTE Crc8_DataArray[], BYTE Crc8_Length)
{
    CANE2E_CRC8_STARTVALUE = CANE2E_CRC8_INITIALVALUE;
    for(int i = 0; i < Crc8_Length; ++i)
    {
        CANE2E_CRC8_STARTVALUE = cane2e_CrcTable8[(CANE2E_CRC8_STARTVALUE ^ Crc8_DataArray[i])]; /* PRQAJ S 492 General usage, no function effect */
    }

    return (BYTE)(CANE2E_CRC8_STARTVALUE ^ CANE2E_CRC8_XORVALUE);
}

void ACRForm::Send121()
{
    QByteArray ba;

    Count_121 = (Count_121 + 1) % 16;
    canfd_data_121.frame.data[6]  =  ba.setNum(Count_121, 16).toInt(nullptr, 16) << 4;

    for(int i =0;i<7;i++){
        txDataBuffer_temp[i] = canfd_data_121.frame.data[i];
    }

    canfd_data_121.frame.data[7] = can_e2e_CalculateCRC8(txDataBuffer_temp, 7);
}

void ACRForm::CreateItem(uint Id, QVector<BYTE> FilterData, std::function<void (const CANData &)> const Func)
{
    QReceiveItem* NewItem = new QReceiveItem;
    NewItem->ConstructTrigger(Id,FilterData,Func);

    Items.append(NewItem);
}

void ACRForm::on_pushButton_clicked()
{
    if(!mainWindow->IsOpenCAN()) return;

    TransmitMessageByTimer(EMessageTimer::Message_121, &canfd_data_121, &ACRForm::Send121, 10, 10);

    TransmitMessageByTimer(EMessageTimer::Message_1C2, &canfd_data_1C2, nullptr, 10, 10);

    TransmitMessageByTimer(EMessageTimer::Message_50,  &canfd_data_50,  nullptr, 10, 500);

    TransmitMessageByTimer(EMessageTimer::Message_288, &canfd_data_288, nullptr, 10, 40);

    TransmitMessageByTimer(EMessageTimer::Message_2D2, &canfd_data_2D2, nullptr, 10, 100);

    TransmitMessageByTimer(EMessageTimer::Message_2F7, &canfd_data_2F7, nullptr, 10, 100);

    TransmitMessageByTimer(EMessageTimer::Message_406, &canfd_data_406, nullptr, 10, 700);
}


void ACRForm::on_pushButton_2_clicked()
{
    if(!mainWindow->IsOpenCAN()) return;

    ZCAN_TransmitFD_Data can_data;

    canid_t CANID     = 0x740;
    BYTE DLC          = 8;
    BYTE TransmitType = 0;

    memset(&can_data, 0, sizeof(can_data));
    can_data.frame.can_id   =  MAKE_CAN_ID(CANID, 0, 0, 0);         // CAN ID
    can_data.frame.len  =  DLC;                                 // CAN 数据长度
    can_data.transmit_type  =  TransmitType;
    can_data.frame.data[0] = 0x03;
    can_data.frame.data[1] = 0x22;
    can_data.frame.data[2] = 0xFD;
    can_data.frame.data[3] = 0x01;

    mainWindow->TransmitCANData(can_data);
}


void ACRForm::on_pushButton_3_clicked()
{
    PerformanceFrequency* temp = new PerformanceFrequency;
    connect(temp, &PerformanceFrequency::TimeOut, this, [=]() -> void
    {
        qDebug()<<"Test";
    });

    temp->setThreadRunning(90);
}

void ACRForm::on_pushButton_4_clicked()
{

}


void ACRForm::on_pushButton_5_clicked()
{
    if(!mainWindow->IsOpenCAN()) return;
    ZCAN_TransmitFD_Data can;
    memset(&can, 0, sizeof(can));
    can.frame.can_id    =  MAKE_CAN_ID(0x740, 0, 0, 0);
    can.frame.len       =  8;
    can.transmit_type   =  0;
    can.frame.data[0]   =  0x02;
    can.frame.data[1]   =  0x10;
    can.frame.data[2]   =  0x03;

    TransmitMessageByTimer(EMessageTimer::Single, can, nullptr, 100);

    memset(&canfd_data_Extended_Session, 0, sizeof(canfd_data_Extended_Session));
    canfd_data_Extended_Session.frame.can_id    =  MAKE_CAN_ID(0x740, 0, 0, 0);
    canfd_data_Extended_Session.frame.len       =  8;
    canfd_data_Extended_Session.transmit_type   =  0;
    canfd_data_Extended_Session.frame.data[0]   =  0x02;
    canfd_data_Extended_Session.frame.data[1]   =  0x3E;
    canfd_data_Extended_Session.frame.data[2]   =  0x00;
    TransmitMessageByTimer(EMessageTimer::Extended_Session, &canfd_data_Extended_Session, nullptr, 500, 4000);

    memset(&can, 0, sizeof(can));
    can.frame.can_id    =  MAKE_CAN_ID(0x740, 0, 0, 0);
    can.frame.len       =  8;
    can.transmit_type   =  0;
    can.frame.data[0]   =  0x02;
    can.frame.data[1]   =  0x27;
    can.frame.data[2]   =  0x61;

    TransmitMessageByTimer(EMessageTimer::Single, can, nullptr, 1000);
}


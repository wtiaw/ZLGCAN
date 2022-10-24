#include "ACRForm.h"
#include "mainwindow.h"
#include <QByteArray>
#include "ui_ACRForm.h"

ACRForm::ACRForm(QWidget *parent, Qt::WindowFlags f) :
    QWidget(parent, f),
    ui(new Ui::ACRForm)
{
    setAttribute(Qt::WA_QuitOnClose, false);

    ui->setupUi(this);

    setWindowTitle(QString("ACR"));

    mainWindow = qobject_cast<MainWindow*>(parent);

    memset(&canfd_data_406, 0, sizeof(canfd_data_406));
    canfd_data_406.frame.can_id   =  MAKE_CAN_ID(0x406, 0, 0, 0);         // CAN ID
    canfd_data_406.frame.len      =  8;                                 // CAN 数据长度
    canfd_data_406.transmit_type  =  0;

    memset(&canfd_data_121, 0, sizeof(canfd_data_121));
    canfd_data_121.frame.can_id   =  MAKE_CAN_ID(0x121, 0, 0, 0);         // CAN ID
    canfd_data_121.frame.len      =  8;                                 // CAN 数据长度
    canfd_data_121.transmit_type  =  0;
    canfd_data_121.frame.data[1]  =  0x20;

    memset(&canfd_data_1C2, 0, sizeof(canfd_data_1C2));
    canfd_data_1C2.frame.can_id    =  MAKE_CAN_ID(0x1C2, 0, 0, 0);         // CAN ID
    canfd_data_1C2.frame.len       =  64;                                 // CAN 数据长度
    canfd_data_1C2.transmit_type   =  0;
    canfd_data_1C2.frame.data[12]   =  0x01;
    canfd_data_1C2.frame.data[16]   =  0x04;
//    canfd_data_1C2.frame.data[12]  =  0x19;
//    canfd_data_1C2.frame.data[20]  =  0xC8;
//    canfd_data_1C2.frame.data[23]  =  0x67;
//    canfd_data_1C2.frame.data[24]  =  0x20;

    memset(&canfd_data_50, 0, sizeof(canfd_data_50));
    canfd_data_50.frame.can_id    =  MAKE_CAN_ID(0x50, 0, 0, 0);         // CAN ID
    canfd_data_50.frame.len       =  8;                                 // CAN 数据长度
    canfd_data_50.transmit_type   =  0;

    memset(&canfd_data_288, 0, sizeof(canfd_data_288));
    canfd_data_288.frame.can_id    =  MAKE_CAN_ID(0x288, 0, 0, 0);         // CAN ID
    canfd_data_288.frame.len       =  8;                                 // CAN 数据长度
    canfd_data_288.transmit_type   =  0;
    canfd_data_288.frame.data[5]   =  0x08;

    memset(&canfd_data_2D2, 0, sizeof(canfd_data_2D2));
    canfd_data_2D2.frame.can_id    =  MAKE_CAN_ID(0x2D2, 0, 0, 0);         // CAN ID
    canfd_data_2D2.frame.len       =  64;                                 // CAN 数据长度
    canfd_data_2D2.transmit_type   =  0;

    memset(&canfd_data_2F7, 0, sizeof(canfd_data_2F7));
    canfd_data_2F7.frame.can_id    =  MAKE_CAN_ID(0x2F7, 0, 0, 0);         // CAN ID
    canfd_data_2F7.frame.len       =  64;                                 // CAN 数据长度
    canfd_data_2F7.transmit_type   =  0;
}

ACRForm::~ACRForm()
{
    delete ui;
}

void ACRForm::TransmitMessageByTimer(EMessageTimer InMessageTimerType, int msec, ZCAN_Transmit_Data *CANData, void (ACRForm::*Function)())
{
    QTimer* Timer = nullptr;
    if(!MessageTimerContainer.contains(InMessageTimerType)){
        Timer = new QTimer;
        Timer->setTimerType(Qt::PreciseTimer);

        connect(Timer, &QTimer::timeout, this, [=]() -> void
        {
            mainWindow->TransmitCAN(*CANData);

            if(Function)
                (this->*Function)();
        });

        MessageTimerContainer.insert(InMessageTimerType, Timer);
    }
    else
    {
        Timer = MessageTimerContainer[InMessageTimerType];
    }

    Timer->start(msec);
}

void ACRForm::TransmitMessageByTimer(EMessageTimer InMessageTimerType, int msec, ZCAN_Transmit_Data &CANData, void (ACRForm::* Function)())
{
    QTimer* Timer = nullptr;
    if(!MessageTimerContainer.contains(InMessageTimerType)){
        Timer = new QTimer;
        Timer->setTimerType(Qt::PreciseTimer);

        connect(Timer, &QTimer::timeout, this, [=]() -> void
        {
            mainWindow->TransmitCAN(CANData);

            if(Function)
                (this->*Function)();
        });

        MessageTimerContainer.insert(InMessageTimerType, Timer);
    }
    else
    {
        Timer = MessageTimerContainer[InMessageTimerType];
    }

    Timer->start(msec);
}

void ACRForm::TransmitMessageByTimer(EMessageTimer InMessageTimerType, int msec, ZCAN_TransmitFD_Data *CANFDData, void (ACRForm::*Function)())
{
    QTimer* Timer = nullptr;
    if(!MessageTimerContainer.contains(InMessageTimerType)){
        Timer = new QTimer;
        Timer->setTimerType(Qt::PreciseTimer);

        connect(Timer, &QTimer::timeout, this, [=]() -> void
        {
            mainWindow->TransmitCANFD(*CANFDData);

            if(Function)
                (this->*Function)();
        });

        MessageTimerContainer.insert(InMessageTimerType, Timer);
    }
    else
    {
        Timer = MessageTimerContainer[InMessageTimerType];
    }

    Timer->start(msec);
}

void ACRForm::TransmitMessageByTimer(EMessageTimer InMessageTimerType, int msec, ZCAN_TransmitFD_Data &CANFDData, void (ACRForm::*Function)())
{
    QTimer* Timer = nullptr;
    if(!MessageTimerContainer.contains(InMessageTimerType)){
        Timer = new QTimer;
        Timer->setTimerType(Qt::PreciseTimer);

        connect(Timer, &QTimer::timeout, this, [=]() -> void
        {
            mainWindow->TransmitCANFD(CANFDData);

            if(Function)
                (this->*Function)();
        });

        MessageTimerContainer.insert(InMessageTimerType, Timer);
    }
    else
    {
        Timer = MessageTimerContainer[InMessageTimerType];
    }

    Timer->start(msec);
}

void ACRForm::StopTimer()
{
    for(auto i : MessageTimerContainer.values())
    {
        i->stop();
    }
}

void ACRForm::ConstructCAN(ZCAN_Transmit_Data &can_data, BYTE DLC, BYTE Data[], BYTE TransmitType)
{

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

void ACRForm::on_pushButton_clicked()
{
    TransmitMessageByTimer(EMessageTimer::Message_121, 10, &canfd_data_121, &ACRForm::Send121);

    TransmitMessageByTimer(EMessageTimer::Message_1C2, 10, &canfd_data_1C2);

    TransmitMessageByTimer(EMessageTimer::Message_50, 500, &canfd_data_50);

    TransmitMessageByTimer(EMessageTimer::Message_288, 40, &canfd_data_288);

    TransmitMessageByTimer(EMessageTimer::Message_2D2, 100, &canfd_data_2D2);

    TransmitMessageByTimer(EMessageTimer::Message_2F7, 100, &canfd_data_2F7);

    TransmitMessageByTimer(EMessageTimer::Message_406, 700, &canfd_data_406);

//    ZCAN_AUTO_TRANSMIT_OBJ auto_can;
//    memset(&auto_can, 0, sizeof(auto_can));
//    auto_can.index = 99;  // 定时列表索引 0
//    auto_can.enable = 1; // 使能此索引，每条可单独设置
//    auto_can.interval = 4000;  // 定时发送间隔 100ms

//    ZCAN_Transmit_Data &can_data = auto_can.obj;
//    canid_t CANID     = 0x406;
//    BYTE DLC          = 8;
//    BYTE TransmitType = 3;

//    memset(&can_data, 0, sizeof(can_data));
//    can_data.frame.can_id   =  MAKE_CAN_ID(CANID, 0, 0, 0);         // CAN ID
//    can_data.frame.can_dlc  =  DLC;                                 // CAN 数据长度
//    can_data.transmit_type  =  TransmitType;                        //发送模式

//    ZCAN_AUTO_TRANSMIT_OBJ auto_can1;
//    memset(&auto_can1, 0, sizeof(auto_can1));
//    auto_can1.index = 98;  // 定时列表索引 0
//    auto_can1.enable = 1; // 使能此索引，每条可单独设置
//    auto_can1.interval = 700;  // 定时发送间隔 100ms

//    ZCAN_Transmit_Data &can_data1 = auto_can1.obj;
//    canid_t CANID1     = 0x406;
//    BYTE DLC1          = 8;
//    BYTE TransmitType1 = 0;

//    memset(&can_data1, 0, sizeof(can_data1));
//    can_data1.frame.can_id   =  MAKE_CAN_ID(CANID1, 0, 0, 0);         // CAN ID
//    can_data1.frame.can_dlc  =  DLC1;                                 // CAN 数据长度
//    can_data1.transmit_type  =  TransmitType1;                        //发送模式

//    mainWindow->GetProperty()->SetValue("0/auto_send", (const char*)&auto_can1);
//    mainWindow->GetProperty()->SetValue("0/auto_send", (const char*)&auto_can);
//    mainWindow->GetProperty()->SetValue("0/apply_auto_send", "0");
}


void ACRForm::on_pushButton_2_clicked()
{
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

    mainWindow->TransmitCANFD(can_data);




//    ZCAN_AUTO_TRANSMIT_OBJ auto_can;

//    memset(&auto_can, 0, sizeof(auto_can));
//    auto_can.index = 98;  // 定时列表索引 0
//    auto_can.enable = 1; // 使能此索引，每条可单独设置
//    auto_can.interval = 4000;  // 定时发送间隔 100ms

//    ZCAN_Transmit_Data &auto_can_data = auto_can.obj;
//    CANID        = 0x740;
//    DLC          = 8;
//    TransmitType = 0;

//    memset(&auto_can_data, 0, sizeof(auto_can_data));
//    auto_can_data.frame.can_id   =  MAKE_CAN_ID(CANID, 0, 0, 0);         // CAN ID
//    auto_can_data.frame.can_dlc  =  DLC;                                 // CAN 数据长度
//    auto_can_data.transmit_type  =  TransmitType;
//    auto_can_data.frame.data[0] = 0x3E;
//    auto_can_data.frame.data[1] = 0x00;

//    mainWindow->GetProperty()->SetValue("0/auto_send", (const char*)&auto_can);
//    mainWindow->GetProperty()->SetValue("0/apply_auto_send", "0");


//    memset(&auto_can, 0, sizeof(auto_can));
//    auto_can.index = 97;  // 定时列表索引 0
//    auto_can.enable = 1; // 使能此索引，每条可单独设置
//    auto_can.interval = 10;  // 定时发送间隔 100ms

//    auto_can_data = auto_can.obj;
//    CANID        = 0x740;
//    DLC          = 8;
//    TransmitType = 0;

//    memset(&auto_can_data, 0, sizeof(auto_can_data));
//    auto_can_data.frame.can_id   =  MAKE_CAN_ID(CANID, 0, 0, 0);         // CAN ID
//    auto_can_data.frame.can_dlc  =  DLC;                                 // CAN 数据长度
//    auto_can_data.transmit_type  =  TransmitType;
//    auto_can_data.frame.data[0] = 0x00;
//    auto_can_data.frame.data[1] = 0x24;

//    mainWindow->GetProperty()->SetValue("0/auto_send", (const char*)&auto_can);
//    mainWindow->GetProperty()->SetValue("0/apply_auto_send", "0");
}


void ACRForm::on_pushButton_3_clicked()
{
    //    ZCAN_Transmit_Data can_data;
    //    canid_t CANID     = 0x111;
    //    BYTE DLC          = 8;
    //    BYTE TransmitType = 0;

    //    memset(&can_data, 0, sizeof(can_data));
    //    can_data.frame.can_id   =  MAKE_CAN_ID(CANID, 0, 0, 0);         // CAN ID
    //    can_data.frame.can_dlc  =  DLC;                                 // CAN 数据长度
    //    can_data.transmit_type  =  TransmitType;

    //    TransmitMessageByTimer(EMessageTimer::NM1,300,can_data);

    //    ZCAN_Transmit_Data can_data1;
    //    canid_t CANID1     = 0x222;
    //    BYTE DLC1          = 8;
    //    BYTE TransmitType1 = 0;

    //    memset(&can_data1, 0, sizeof(can_data1));
    //    can_data1.frame.can_id   =  MAKE_CAN_ID(CANID1, 0, 0, 0);         // CAN ID
    //    can_data1.frame.can_dlc  =  DLC1;                                 // CAN 数据长度
    //    can_data1.transmit_type  =  TransmitType1;

    //    TransmitMessageByTimer(EMessageTimer::NM2,3000,can_data1);
}


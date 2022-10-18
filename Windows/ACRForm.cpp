#include "ACRForm.h"
#include "mainwindow.h"
#include "ui_ACRForm.h"

ACRForm::ACRForm(QWidget *parent, Qt::WindowFlags f) :
    QWidget(parent, f),
    ui(new Ui::ACRForm)
{
    setAttribute(Qt::WA_QuitOnClose, false);

    ui->setupUi(this);

    setWindowTitle(QString("ACR"));

    mainWindow = qobject_cast<MainWindow*>(parent);
}

ACRForm::~ACRForm()
{
    delete ui;
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

void ACRForm::on_pushButton_clicked()
{
    ZCAN_AUTO_TRANSMIT_OBJ auto_can;


    memset(&auto_can, 0, sizeof(auto_can));
    auto_can.index = 99;  // 定时列表索引 0
    auto_can.enable = 1; // 使能此索引，每条可单独设置
    auto_can.interval = 700;  // 定时发送间隔 100ms

    ZCAN_Transmit_Data &can_data = auto_can.obj;
    canid_t CANID     = 0x406;
    BYTE DLC          = 8;
    BYTE TransmitType = 0;

    memset(&can_data, 0, sizeof(can_data));
    can_data.frame.can_id   =  MAKE_CAN_ID(CANID, 0, 0, 0);         // CAN ID
    can_data.frame.can_dlc  =  DLC;                                 // CAN 数据长度
    can_data.transmit_type  =  TransmitType;                        //发送模式

    mainWindow->GetProperty()->SetValue("0/auto_send", (const char*)&auto_can);
    mainWindow->GetProperty()->SetValue("0/apply_auto_send", "0");
}


void ACRForm::on_pushButton_2_clicked()
{
    ZCAN_Transmit_Data can_data;

    canid_t CANID     = 0x740;
    BYTE DLC          = 8;
    BYTE TransmitType = 0;

    memset(&can_data, 0, sizeof(can_data));
    can_data.frame.can_id   =  MAKE_CAN_ID(CANID, 0, 0, 0);         // CAN ID
    can_data.frame.can_dlc  =  DLC;                                 // CAN 数据长度
    can_data.transmit_type  =  TransmitType;
    can_data.frame.data[0] = 0x10;
    can_data.frame.data[1] = 0x03;

    ZCAN_Transmit(mainWindow->GetChannelHandle(), &can_data, 1);



    ZCAN_AUTO_TRANSMIT_OBJ auto_can;

    memset(&auto_can, 0, sizeof(auto_can));
    auto_can.index = 98;  // 定时列表索引 0
    auto_can.enable = 1; // 使能此索引，每条可单独设置
    auto_can.interval = 4000;  // 定时发送间隔 100ms

    ZCAN_Transmit_Data &auto_can_data = auto_can.obj;
    CANID        = 0x740;
    DLC          = 8;
    TransmitType = 0;

    memset(&auto_can_data, 0, sizeof(auto_can_data));
    auto_can_data.frame.can_id   =  MAKE_CAN_ID(CANID, 0, 0, 0);         // CAN ID
    auto_can_data.frame.can_dlc  =  DLC;                                 // CAN 数据长度
    auto_can_data.transmit_type  =  TransmitType;
    auto_can_data.frame.data[0] = 0x3E;
    auto_can_data.frame.data[1] = 0x00;

    mainWindow->GetProperty()->SetValue("0/auto_send", (const char*)&auto_can);
    mainWindow->GetProperty()->SetValue("0/apply_auto_send", "0");


    memset(&auto_can, 0, sizeof(auto_can));
    auto_can.index = 97;  // 定时列表索引 0
    auto_can.enable = 1; // 使能此索引，每条可单独设置
    auto_can.interval = 10;  // 定时发送间隔 100ms

    auto_can_data = auto_can.obj;
    CANID        = 0x740;
    DLC          = 8;
    TransmitType = 0;

    memset(&auto_can_data, 0, sizeof(auto_can_data));
    auto_can_data.frame.can_id   =  MAKE_CAN_ID(CANID, 0, 0, 0);         // CAN ID
    auto_can_data.frame.can_dlc  =  DLC;                                 // CAN 数据长度
    auto_can_data.transmit_type  =  TransmitType;
    auto_can_data.frame.data[0] = 0x00;
    auto_can_data.frame.data[1] = 0x24;

    mainWindow->GetProperty()->SetValue("0/auto_send", (const char*)&auto_can);
    mainWindow->GetProperty()->SetValue("0/apply_auto_send", "0");
}


void ACRForm::on_pushButton_3_clicked()
{

}


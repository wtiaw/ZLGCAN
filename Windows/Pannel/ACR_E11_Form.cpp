#include "ACR_E11_Form.h"
#include "CustomThread/QReceiveItem.h"
#include "mainwindow.h"
#include <QByteArray>
#include <QtConcurrent>
#include <utility>
#include "ui_ACR_E11_Form.h"
#include "zlgcan.h"
#include "CustomThread/QReceiveThread.h"

ACR_E11_Form::ACR_E11_Form(QWidget* parent, Qt::WindowFlags f) :
    FormBase(parent, f),
    ui(new Ui::ACR_E11_Form)
{
    setAttribute(Qt::WA_QuitOnClose, false);

    ui->setupUi(this);

    setWindowTitle(QString("ACR"));
    FromType = CustomEnum::EFormType::ACR_E11;

    mainWindow = qobject_cast<MainWindow*>(parent);

    Init();
}

ACR_E11_Form::~ACR_E11_Form()
{
    delete ui;
}

void ACR_E11_Form::TransmitMessageByTimer(EMessageTimer InMessageTimerType, ZCAN_Transmit_Data* CANData,
                                     void (ACR_E11_Form::*Function)(), uint delay, uint msec)
{
    TransmitMessageByTimer<ZCAN_Transmit_Data>(InMessageTimerType, CANData, Function, delay, msec);
}

void ACR_E11_Form::TransmitMessageByTimer(EMessageTimer InMessageTimerType, ZCAN_TransmitFD_Data* CANData,
                                     void (ACR_E11_Form::*Function)(), uint delay, uint msec)
{
    if (!cHandle)
        cHandle = mainWindow->GetChannelHandle();

    PerformanceFrequency* temp;
    if (!MessageThreadContainer.contains(InMessageTimerType))
    {
        temp = new PerformanceFrequency;

        connect(temp, &PerformanceFrequency::TimeOut, this, [=]() mutable -> void
        {
            mainWindow->TransmitCANDataObj(*CANData);

            if (Function)
                (this->*Function)();
        }, Qt::QueuedConnection);

        if (InMessageTimerType != EMessageTimer::Single)
            MessageThreadContainer.insert(InMessageTimerType, temp);
    }
    else
    {
        temp = MessageThreadContainer[InMessageTimerType];
    }

    temp->SetThreadRunning(delay, InMessageTimerType == EMessageTimer::Single, msec);
}

void ACR_E11_Form::StopTimer() const
{
    for (const auto i : MessageThreadContainer.values())
    {
        i->SetThreadStop();
    }

    for (const auto& i : MessageTimerContainer.values())
    {
        i->stop();
    }
}

void ACR_E11_Form::InitWindow()
{
    FormBase::InitWindow();
    
    ui->BSW->setText("---");
    ui->SV->setText("---");
    ui->FBL->setText("---");

    ui->ACR_Key->setText("0");
    ui->ACRCrcChk122->setText("0");
    ui->ACRCycCntr122->setText("0");
    ui->Activation_Status->setText("0");

    ui->Tem->setText("0");
    ui->VHBH_Phy->setText("0");
    ui->VHBL_Phy->setText("0");
    ui->CANW->setText("0");
}

void ACR_E11_Form::InitButtonFunction()
{
    FormBase::InitButtonFunction();
}

void ACR_E11_Form::InitTrigger()
{
    const auto ReceiveThread = mainWindow->ReceiveThread;

    QVector<BYTE> Temp;

    CreateItem(0x122, Temp, [&](const CANData& Data)
    {
        ui->ACR_Key->setText(QString::number(Data.Data[4]));
        ui->ACRCrcChk122->setText(QString::number(Data.Data[6] >> 4, 16));
        ui->ACRCycCntr122->setText(QString::number(Data.Data[7], 16));
        ui->Activation_Status->setText(QString::number(Data.Data[1]));
    });

    //读版本
    Temp = {0x07, 0x62, 0xFD, 0x01};
    CreateItem(0x748, Temp, [&](const CANData& Data)
    {
        ZCAN_TransmitFD_Data can_data = {};

        can_data.frame.can_id = MAKE_CAN_ID(0x740, 0, 0, 0); // CAN ID
        can_data.frame.len = 8; // CAN 数据长度
        can_data.transmit_type = 0;
        can_data.frame.data[0] = 0x03;
        can_data.frame.data[1] = 0x22;
        can_data.frame.data[2] = 0xFD;
        can_data.frame.data[3] = 0x07;

        emit TransmitCANFD(can_data);

        char string_version[5] = {0};
        for (int i = 0; i < 4; i++)
        {
            string_version[i] = Data.Data[i + 4];
        }
        ui->FBL->setText(string_version);
    });

    Temp = {0x62, 0xFD};
    CreateItem(0x748, Temp, [&](const CANData& Data)
    {
        char string_version[31];
        for (int i = 0; i < 30; i++)
        {
            string_version[i] = Data.Data[i + 3];
        }
        ui->BSW->setText(string_version);
    });


    Temp = {0x06, 0x67, 0x61};
    CreateItem(0x748, Temp, [&](const CANData& Data)
    {
        ZCAN_TransmitFD_Data can_data = {};

        can_data.frame.can_id = MAKE_CAN_ID(0x740, 0, 0, 0); // CAN ID
        can_data.frame.len = 8; // CAN 数据长度
        can_data.transmit_type = 0;
        can_data.frame.data[0] = 0x06;
        can_data.frame.data[1] = 0x27;
        can_data.frame.data[2] = 0x62;
        can_data.frame.data[3] = ~Data.Data[3];
        can_data.frame.data[4] = ~Data.Data[4];
        can_data.frame.data[5] = ~Data.Data[5];
        can_data.frame.data[6] = ~Data.Data[6];

        emit TransmitCANFD(can_data);
    });

    Temp = {0x02, 0x67, 0x62};
    CreateItem(0x748, Temp, [&]([[maybe_unused]] const CANData& Data)
    {
        ZCAN_TransmitFD_Data can_data = {};

        can_data.frame.can_id = MAKE_CAN_ID(0x740, 0, 0, 0); // CAN ID
        can_data.frame.len = 8; // CAN 数据长度
        can_data.transmit_type = 0;
        can_data.frame.data[0] = 0x07;
        can_data.frame.data[1] = 0x31;
        can_data.frame.data[2] = 0x01;
        can_data.frame.data[3] = 0xFD;
        can_data.frame.data[4] = 0x0A;
        can_data.frame.data[5] = 0x00;
        can_data.frame.data[6] = 0x28;
        can_data.frame.data[7] = 0xAC;

        emit TransmitCANFD(can_data);
    });

    Temp = {0x07, 0x71, 0x01, 0xFD, 0x0A, 0x00};
    CreateItem(0x748, Temp, [&](const CANData& Data)
    {
        ZCAN_TransmitFD_Data can_data = {};

        can_data.frame.can_id = MAKE_CAN_ID(0x740, 0, 0, 0); // CAN ID
        can_data.frame.len = 8; // CAN 数据长度
        can_data.transmit_type = 0;
        can_data.frame.data[0] = 0x07;
        can_data.frame.data[1] = 0x31;
        can_data.frame.data[2] = 0x01;
        can_data.frame.data[3] = 0xFD;
        can_data.frame.data[4] = 0x0F;
        can_data.frame.data[5] = 0x00;
        can_data.frame.data[6] = ~Data.Data[6];
        can_data.frame.data[7] = ~Data.Data[7];

        emit TransmitCANFD(can_data);
    });

    Temp = {0x71, 0x01, 0xFD, 0x0F};
    CreateItem(0x748, Temp, [&](const CANData& Data)
    {
        char string_version[7];
        for (int i = 0; i < 6; i++)
        {
            string_version[i] = Data.Data[i + 4];
        }
        ui->SV->setText(string_version);

        emit TransmitCANFD(canfd_data_GW740);
    });

    Temp = {0x06, 0x50, 0x03, 0x00, 0x32, 0x01, 0xF4};
    CreateItem(0x748, Temp, [&]([[maybe_unused]] const CANData& Data)
    {
        ZCAN_TransmitFD_Data can = {};
        can.frame.can_id = MAKE_CAN_ID(0x740, 0, 0, 0);
        can.frame.len = 8;
        can.transmit_type = 0;
        can.frame.data[0] = 0x02;
        can.frame.data[1] = 0x27;
        can.frame.data[2] = 0x61;

        emit TransmitCANFD(can);
    });

    Temp = {0x07, 0x71, 0x01, 0xCF, 0x81};
    CreateItem(0x748, Temp, [&](const CANData& Data)
    {
        int hex_value;
        switch (Data.Data[5])
        {
        case 0x02:
            {
                hex_value = (Data.Data[6] << 8) | Data.Data[7];
                ui->Tem->setText(QString::number(hex_value / 100.f));
                break;
            }
        case 0x03:
            {
                hex_value = (Data.Data[6] << 8) | Data.Data[7];
                ui->VHBH_Phy->setText(QString::number(hex_value));
                break;
            }
        case 0x04:
            {
                hex_value = (Data.Data[6] << 8) | Data.Data[7];
                ui->VHBL_Phy->setText(QString::number(hex_value));
                break;
            }
        case 0x06:
            {
                hex_value = (Data.Data[6] << 8) | Data.Data[7];
                ui->CANW->setText(QString::number(hex_value));
                break;
            }
        }

        SendGW740();

        emit TransmitCANFD(canfd_data_GW740);
    });

    ReceiveThread->AddTrigger(Items);
    qDebug() << "init";
}

void ACR_E11_Form::Init()
{
    InitTrigger();

    InitReqButton();

    memset(&canfd_data_406, 0, sizeof(canfd_data_406));
    canfd_data_406.frame.can_id = MAKE_CAN_ID(0x406, 0, 0, 0);
    canfd_data_406.frame.len = 8;
    canfd_data_406.transmit_type = 0;

    memset(&canfd_data_121, 0, sizeof(canfd_data_121));
    canfd_data_121.frame.can_id = MAKE_CAN_ID(0x121, 0, 0, 0);
    canfd_data_121.frame.len = 8;
    canfd_data_121.transmit_type = 0;
    canfd_data_121.frame.data[1] = 0x20;

    memset(&canfd_data_1C2, 0, sizeof(canfd_data_1C2));
    canfd_data_1C2.frame.can_id = MAKE_CAN_ID(0x1C2, 0, 0, 0);
    canfd_data_1C2.frame.len = 64;
    canfd_data_1C2.transmit_type = 0;
    canfd_data_1C2.frame.data[11] = 0x01;
    canfd_data_1C2.frame.data[15] = 0x04;

    memset(&canfd_data_50, 0, sizeof(canfd_data_50));
    canfd_data_50.frame.can_id = MAKE_CAN_ID(0x50, 0, 0, 0);
    canfd_data_50.frame.len = 8;
    canfd_data_50.transmit_type = 0;

    memset(&canfd_data_288, 0, sizeof(canfd_data_288));
    canfd_data_288.frame.can_id = MAKE_CAN_ID(0x288, 0, 0, 0);
    canfd_data_288.frame.len = 8;
    canfd_data_288.transmit_type = 0;
    canfd_data_288.frame.data[5] = 0x08;

    memset(&canfd_data_2D2, 0, sizeof(canfd_data_2D2));
    canfd_data_2D2.frame.can_id = MAKE_CAN_ID(0x2D2, 0, 0, 0);
    canfd_data_2D2.frame.len = 64;
    canfd_data_2D2.transmit_type = 0;

    memset(&canfd_data_2F7, 0, sizeof(canfd_data_2F7));
    canfd_data_2F7.frame.can_id = MAKE_CAN_ID(0x2F7, 0, 0, 0);
    canfd_data_2F7.frame.len = 64;
    canfd_data_2F7.transmit_type = 0;

    memset(&canfd_data_GW740, 0, sizeof(canfd_data_GW740));
    canfd_data_GW740.frame.can_id = MAKE_CAN_ID(0x740, 0, 0, 0);
    canfd_data_GW740.frame.len = 8;
    canfd_data_GW740.transmit_type = 0;
    canfd_data_GW740.frame.data[0] = 0x07;
    canfd_data_GW740.frame.data[1] = 0x31;
    canfd_data_GW740.frame.data[2] = 0x01;
    canfd_data_GW740.frame.data[3] = 0xCF;
    canfd_data_GW740.frame.data[4] = 0x81;

    ACR_E11_Form::InitWindow();
    connect(this, SIGNAL(TransmitCANFD(ZCAN_TransmitFD_Data&)), mainWindow,
            SLOT(TransmitCANDataObj(ZCAN_TransmitFD_Data&)));
}

void ACR_E11_Form::InitReqButton()
{
    ui->ACR_Req_LH->clear();

    const auto Value = QSystemVariables::Variables.value("VCU").Variables.value("ACR_Req_LH").ValueTables;
    for (auto i : Value)
    {
        ui->ACR_Req_LH->addItem(i.DisplayName);
    }
}

BYTE ACR_E11_Form::CAN_E2E_CalcuelateCRC8(BYTE Crc8_DataArray[], BYTE Crc8_Length)
{
    CANE2E_CRC8_STARTVALUE = CANE2E_CRC8_INITIALVALUE;
    for (int i = 0; i < Crc8_Length; ++i)
    {
        CANE2E_CRC8_STARTVALUE = cane2e_CrcTable8[(CANE2E_CRC8_STARTVALUE ^ Crc8_DataArray[i])];
        /* PRQAJ S 492 General usage, no function effect */
    }

    return static_cast<BYTE>(CANE2E_CRC8_STARTVALUE ^ CANE2E_CRC8_XORVALUE);
}

void ACR_E11_Form::Send121()
{
    QByteArray ba;
    
    canfd_data_121.frame.data[0] = ui->ACR_Req_LH->currentIndex();

    Count_121 = (Count_121 + 1) % 16;
    canfd_data_121.frame.data[6] = ba.setNum(Count_121, 16).toInt(nullptr, 16) << 4;

    for (int i = 0; i < 7; i++)
    {
        txDataBuffer_temp[i] = canfd_data_121.frame.data[i];
    }

    canfd_data_121.frame.data[7] = CAN_E2E_CalcuelateCRC8(txDataBuffer_temp, 7);
}

void ACR_E11_Form::SendGW740()
{
    if (++Count_GW740 == 7) Count_GW740++;
    Count_GW740 %= 10;

    canfd_data_GW740.frame.data[7] = Count_GW740;
}

void ACR_E11_Form::CreateItem(uint Id, QVector<BYTE> FilterData, std::function<void (const CANData&)> const Func)
{
    auto* NewItem = new QReceiveItem;
    NewItem->ConstructTrigger(Id, std::move(FilterData), this, Func);

    Items.append(NewItem);
}

void ACR_E11_Form::on_pushButton_clicked()
{
    if (!mainWindow->IsOpenCAN()) return;

    TransmitMessageByTimer(EMessageTimer::Message_121, &canfd_data_121, &ACR_E11_Form::Send121, 10, 10);
    TransmitMessageByTimer(EMessageTimer::Message_1C2, &canfd_data_1C2, nullptr, 10, 10);
    TransmitMessageByTimer(EMessageTimer::Message_50, &canfd_data_50, nullptr, 10, 500);
    TransmitMessageByTimer(EMessageTimer::Message_288, &canfd_data_288, nullptr, 10, 40);
    TransmitMessageByTimer(EMessageTimer::Message_2D2, &canfd_data_2D2, nullptr, 10, 100);
    TransmitMessageByTimer(EMessageTimer::Message_2F7, &canfd_data_2F7, nullptr, 10, 100);
    TransmitMessageByTimer(EMessageTimer::Message_406, &canfd_data_406, nullptr, 10, 700);
}


void ACR_E11_Form::on_pushButton_2_clicked()
{
    if (!mainWindow->IsOpenCAN()) return;

    ZCAN_TransmitFD_Data can_data;

    constexpr canid_t CANID = 0x740;
    constexpr BYTE DLC = 8;
    constexpr BYTE TransmitType = 0;

    memset(&can_data, 0, sizeof(can_data));
    can_data.frame.can_id = MAKE_CAN_ID(CANID, 0, 0, 0); // CAN ID
    can_data.frame.len = DLC; // CAN 数据长度
    can_data.transmit_type = TransmitType;
    can_data.frame.data[0] = 0x03;
    can_data.frame.data[1] = 0x22;
    can_data.frame.data[2] = 0xFD;
    can_data.frame.data[3] = 0x01;

    mainWindow->TransmitCANDataObj(can_data);
}

void ACR_E11_Form::on_pushButton_5_clicked()
{
    if (!mainWindow->IsOpenCAN()) return;
    ZCAN_TransmitFD_Data can = {};
    can.frame.can_id = MAKE_CAN_ID(0x740, 0, 0, 0);
    can.frame.len = 8;
    can.transmit_type = 0;
    can.frame.data[0] = 0x02;
    can.frame.data[1] = 0x10;
    can.frame.data[2] = 0x03;

    emit TransmitCANFD(can);
}
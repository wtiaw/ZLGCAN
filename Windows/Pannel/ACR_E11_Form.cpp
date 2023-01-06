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

// void ACR_E11_Form::StopTimer() const
// {
//     for (const auto i : MessageThreadContainer.values())
//     {
//         i->SetThreadStop();
//     }
//
//     for (const auto& i : MessageTimerContainer.values())
//     {
//         i->stop();
//     }
// }

void ACR_E11_Form::InitWindow()
{
    FormBase::InitWindow();

    InitComboBox(ui->CB_ACR_Req_LH, "VCU", "ACR_Req_LH");
    for (auto i : CB_PollingDataComboBoxes)
    {
        InitComboBox(i, "PollingData", "PollingVariable_1");
        i->setCurrentIndex(i->count() - 1);
    }

    ui->DD_BSW->SetDataDisplay("---");
    ui->DD_SV->SetDataDisplay("---");
    ui->DD_FBL->SetDataDisplay("---");

    ui->DD_ACR_Key->SetDataDisplay("0");
    ui->DD_ACRCrcChk122->SetDataDisplay("0");
    ui->DD_ACRCycCntr122->SetDataDisplay("0");
    ui->DD_Activation_Status->SetDataDisplay("0");

    ui->DD_TEM_Phy->SetDataDisplay("0");
    ui->DD_VHBH_Phy->SetDataDisplay("0");
    ui->DD_VHBL_Phy->SetDataDisplay("0");
    ui->DD_CANW_Phy->SetDataDisplay("0");

    ui->DD_PollingData1->SetDataDisplay("---");
    ui->DD_PollingData2->SetDataDisplay("---");
    ui->DD_PollingData3->SetDataDisplay("---");
    ui->DD_PollingData4->SetDataDisplay("---");
    ui->DD_PollingData5->SetDataDisplay("---");
}

void ACR_E11_Form::InitButtonFunction()
{
    FormBase::InitButtonFunction();

    connect(this, SIGNAL(TransmitCANFD(ZCAN_TransmitFD_Data&)), mainWindow,
            SLOT(TransmitCANDataObj(ZCAN_TransmitFD_Data&)), Qt::UniqueConnection);
    connect(ui->CB_ACR_Req_LH, &QComboBox::currentIndexChanged, this,
            &ACR_E11_Form::On_ACR_Req_LH_ComboBox_CurrentIndexChanged, Qt::UniqueConnection);

    connect(ui->BT_WakeUp, &QPushButton::clicked, this, &ACR_E11_Form::On_WakeUp, Qt::UniqueConnection);
    connect(ui->BT_ReadVersion, &QPushButton::clicked, this, &ACR_E11_Form::On_ReadVersion, Qt::UniqueConnection);
    connect(ui->BT_UnLock, &QPushButton::clicked, this, &ACR_E11_Form::On_UnLock, Qt::UniqueConnection);
}

void ACR_E11_Form::InitTrigger()
{
    const auto ReceiveThread = mainWindow->ReceiveThread;
    ReceiveThread->ClearTrigger();

    QVector<BYTE> Temp;

    CreateItem(0x122, Temp, [&](const CANData& Data)
    {
        ui->DD_ACR_Key->SetDataDisplay(QString::number(Data.Data[4]));
        ui->DD_ACRCrcChk122->SetDataDisplay(QString::number(Data.Data[6] >> 4, 16));
        ui->DD_ACRCycCntr122->SetDataDisplay(QString::number(Data.Data[7], 16));
        ui->DD_Activation_Status->SetDataDisplay(QString::number(Data.Data[1]));
    });

    //读FBL
    Temp = {0x07, 0x62, 0xFD, 0x01};
    CreateItem(0x748, Temp, [this](auto&& PH1) { ReqReadBSW_and_AnalyzingFBL(std::forward<decltype(PH1)>(PH1)); });

    //读BSW
    Temp = {0x62, 0xFD};
    CreateItem(0x748, Temp, [this](auto&& PH1) { AnalyzingBSW(std::forward<decltype(PH1)>(PH1)); });

    //进入拓展会话
    Temp = {0x06, 0x50, 0x03};
    CreateItem(0x748, Temp, [this](auto&& PH1) { ReqSeed(std::forward<decltype(PH1)>(PH1)); });

    //请求到seed
    Temp = {0x06, 0x67, 0x61};
    CreateItem(0x748, Temp, [this](auto&& PH1) { SendKey(std::forward<decltype(PH1)>(PH1)); });

    //Key校验通过
    Temp = {0x02, 0x67, 0x62};
    CreateItem(0x748, Temp, [this](auto&& PH1) { ReqUnlockECU(std::forward<decltype(PH1)>(PH1)); });

    //ECU解锁成功
    Temp = {0x07, 0x71, 0x01, 0xFD, 0x0A, 0x00};
    CreateItem(0x748, Temp, [this](auto&& PH1) { ReqReadSV(std::forward<decltype(PH1)>(PH1)); });

    //读取SV
    Temp = {0x71, 0x01, 0xFD, 0x0F};
    CreateItem(0x748, Temp, [this](auto&& PH1) { ReadSV_and_ReadState(std::forward<decltype(PH1)>(PH1)); });

    //周期读数据
    Temp = {0x07, 0x71, 0x01, 0xCF, 0x81};
    CreateItem(0x748, Temp, [&](const CANData& Data)
    {
        AnalyzingUnderlyingData(Data);

        SendGW740();

        emit TransmitCANFD(canfd_data_GW740);
    });

    ReceiveThread->AddTrigger(Items);
}

void ACR_E11_Form::InitComboBox(QComboBox* ComboBox, const QString& Namespace, const QString& VariableName)
{
    ComboBox->clear();

    for (auto i : QSystemVariables::GetVariablesByNamespaceAndName(Namespace, VariableName))
    {
        ComboBox->addItem(i.DisplayName);
    }
}

void ACR_E11_Form::Init()
{
    FormBase::Init();

    InitTrigger();

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
}

void ACR_E11_Form::InitVariable()
{
    CB_PollingDataComboBoxes.append(ui->CB_PollingData1);
    CB_PollingDataComboBoxes.append(ui->CB_PollingData2);
    CB_PollingDataComboBoxes.append(ui->CB_PollingData3);
    CB_PollingDataComboBoxes.append(ui->CB_PollingData4);
    CB_PollingDataComboBoxes.append(ui->CB_PollingData5);
}

BYTE ACR_E11_Form::CAN_E2E_CalcuelateCRC8(BYTE Crc8_DataArray[], BYTE Crc8_Length)
{
    CANE2E_CRC8_STARTVALUE = CANE2E_CRC8_INITIALVALUE;
    for (int i = 0; i < Crc8_Length; ++i)
    {
        CANE2E_CRC8_STARTVALUE = cane2e_CrcTable8[(CANE2E_CRC8_STARTVALUE ^ Crc8_DataArray[i])];
    }

    return static_cast<BYTE>(CANE2E_CRC8_STARTVALUE ^ CANE2E_CRC8_XORVALUE);
}

void ACR_E11_Form::Send121()
{
    QByteArray ba;

    const auto VariableBase = QSystemVariables::GetVariableBaseByNamespaceAndName("VCU", "ACR_Req_LH");
    canfd_data_121.frame.data[0] = VariableBase->GetCurrentValue().toInt();

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

void ACR_E11_Form::On_WakeUp()
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


void ACR_E11_Form::On_ReadVersion()
{
    if (!mainWindow->IsOpenCAN()) return;

    ReqReadFBL();
}

void ACR_E11_Form::On_UnLock()
{
    if (!mainWindow->IsOpenCAN()) return;

    EnterExtendSession();
}

void ACR_E11_Form::On_ACR_Req_LH_ComboBox_CurrentIndexChanged(int index)
{
    QVariableBase* VariableBase = QSystemVariables::GetVariableBaseByNamespaceAndName("VCU", "ACR_Req_LH");

    if (!VariableBase) return;
    const int CurrentValue = GetTableValueByIndex(VariableBase->ValueTables, index);

    VariableBase->SetCurrentValue(CurrentValue);
    // auto test = QSystemVariables::NeedSaveVariables.first();
    //
    // qDebug() << test.Namespace + "::" + test.Name<<GET_VARIABLE_NAME(test.Namespace,test.Name);
}

void ACR_E11_Form::ReqReadFBL()
{
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

void ACR_E11_Form::ReqReadBSW_and_AnalyzingFBL(const CANData& Data)
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
    ui->DD_FBL->SetDataDisplay(string_version);
}

void ACR_E11_Form::AnalyzingBSW(const CANData& Data)
{
    char string_version[31];
    for (int i = 0; i < 30; i++)
    {
        string_version[i] = Data.Data[i + 3];
    }
    ui->DD_BSW->SetDataDisplay(string_version);
}

void ACR_E11_Form::EnterExtendSession()
{
    ZCAN_TransmitFD_Data can = {};
    can.frame.can_id = MAKE_CAN_ID(0x740, 0, 0, 0);
    can.frame.len = 8;
    can.transmit_type = 0;
    can.frame.data[0] = 0x02;
    can.frame.data[1] = 0x10;
    can.frame.data[2] = 0x03;

    emit TransmitCANFD(can);
}

void ACR_E11_Form::ReqSeed(const CANData& Data)
{
    ZCAN_TransmitFD_Data can = {};
    can.frame.can_id = MAKE_CAN_ID(0x740, 0, 0, 0);
    can.frame.len = 8;
    can.transmit_type = 0;
    can.frame.data[0] = 0x02;
    can.frame.data[1] = 0x27;
    can.frame.data[2] = 0x61;

    emit TransmitCANFD(can);
}

void ACR_E11_Form::SendKey(const CANData& Data)
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
}

void ACR_E11_Form::ReqUnlockECU(const CANData& Data)
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
}

void ACR_E11_Form::ReqReadSV(const CANData& Data)
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
}

void ACR_E11_Form::ReadSV_and_ReadState(const CANData& Data)
{
    char string_version[7];
    for (int i = 0; i < 6; i++)
    {
        string_version[i] = Data.Data[i + 4];
    }
    ui->DD_SV->SetDataDisplay(string_version);

    emit TransmitCANFD(canfd_data_GW740);
}

void ACR_E11_Form::AnalyzingUnderlyingData(const CANData& Data)
{
    int hex_value;
    switch (Data.Data[5])
    {
    //I_A_VCC_M
    case 0x00:
        {
            hex_value = (Data.Data[6] << 8) | Data.Data[7];

            const auto Variable = QSystemVariables::GetVariableBaseByNamespaceAndName("ACR_Probe", "I_A_VCC_M");
            Variable->SetCurrentValue(hex_value);

            ui->DD_VCC_Phy->SetDataDisplay(Variable->GetCurrentValue());
            break;
        }
    //I_A_VBAT_M
    case 0x01:
        {
            hex_value = (Data.Data[6] << 8) | Data.Data[7];

            const auto Variable = QSystemVariables::GetVariableBaseByNamespaceAndName("ACR_Probe", "I_A_VBAT_M");
            Variable->SetCurrentValue(hex_value);

            ui->DD_VBAT_Phy->SetDataDisplay(Variable->GetCurrentValue());
            break;
        }
    //I_A_TEM_M
    case 0x02:
        {
            hex_value = (Data.Data[6] << 8) | Data.Data[7];

            const auto Variable = QSystemVariables::GetVariableBaseByNamespaceAndName("ACR_Probe", "I_A_TEM_M");
            Variable->SetCurrentValue((hex_value / 100.f));

            ui->DD_TEM_Phy->SetDataDisplay(Variable->GetCurrentValue());
            break;
        }
    //I_A_VHBH_M
    case 0x03:
        {
            hex_value = (Data.Data[6] << 8) | Data.Data[7];

            const auto Variable = QSystemVariables::GetVariableBaseByNamespaceAndName("ACR_Probe", "I_A_VHBH_M");
            Variable->SetCurrentValue(hex_value);

            ui->DD_VHBH_Phy->SetDataDisplay(Variable->GetCurrentValue());
            break;
        }
    //I_A_VHBL_M
    case 0x04:
        {
            hex_value = (Data.Data[6] << 8) | Data.Data[7];

            const auto Variable = QSystemVariables::GetVariableBaseByNamespaceAndName("ACR_Probe", "I_A_VHBL_M");
            Variable->SetCurrentValue(hex_value);

            ui->DD_VHBL_Phy->SetDataDisplay(Variable->GetCurrentValue());
            break;
        }
    //I_A_CURRENT_M
    case 0x05:
        {
            hex_value = (Data.Data[6] << 8) | Data.Data[7];

            const auto Variable = QSystemVariables::GetVariableBaseByNamespaceAndName("ACR_Probe", "I_A_CURRENT_M");
            Variable->SetCurrentValue((hex_value - 32767) / 100.f);

            ui->DD_CUR_Phy->SetDataDisplay(Variable->GetCurrentValue());
            break;
        }
    //I_A_CANWAKE_M
    case 0x06:
        {
            hex_value = (Data.Data[6] << 8) | Data.Data[7];

            const auto Variable = QSystemVariables::GetVariableBaseByNamespaceAndName("ACR_Probe", "I_A_CANWAKE_M");
            Variable->SetCurrentValue(hex_value);

            ui->DD_CANW_Phy->SetDataDisplay(Variable->GetCurrentValue());
            break;
        }
    //I_D_HALLSPD_M
    case 0x09:
        {
            hex_value = (Data.Data[6] << 8) | Data.Data[7];

            const auto Variable = QSystemVariables::GetVariableBaseByNamespaceAndName("ACR_Probe", "I_D_HALLSPD_M");
            Variable->SetCurrentValue(hex_value - 32767);

            ui->DD_HSPD_Phy->SetDataDisplay(Variable->GetCurrentValue());
            break;
        }
    }
}

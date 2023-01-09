#ifndef ACRFORM_H
#define ACRFORM_H

#include <DataDisplayWidget.h>

#include "CustomThread/PerformanceFrequency.h"
#include "CustomThread/QReceiveItem.h"
#include "mainwindow.h"
#include "qtimer.h"
#include "typedef.h"
#include <QWidget>

#include "FormBase.h"

namespace Ui
{
    class ACR_E11_Form;
}

enum EMessageTimer
{
    Single,
    Extended_Session,
    Message_406,
    Message_121,
    Message_1C2,
    Message_50,
    Message_288,
    Message_2D2,
    Message_2F7,
    Message_GW740,
};

class ACR_E11_Form final : public FormBase
{
    Q_OBJECT

public:
    explicit ACR_E11_Form(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~ACR_E11_Form() override;


    void TransmitMessageByTimer(EMessageTimer InMessageTimerType, ZCAN_Transmit_Data* CANData,
                                void (ACR_E11_Form::*Function)() = nullptr, uint delay = 1000, uint msec = 100);
    void TransmitMessageByTimer(EMessageTimer InMessageTimerType, ZCAN_TransmitFD_Data* CANData,
                                void (ACR_E11_Form::*Function)() = nullptr, uint delay = 1000, uint msec = 100);

    // void StopTimer() const;

    void InitWindow() override;

protected:
    //Interface
    void InitButtonFunction() override;
    void Init() override;
    void InitVariable() override;

public:
signals:
    void TransmitCANFD(ZCAN_TransmitFD_Data& canfd_data);

private:
    void InitTrigger();

    void InitComboBox(QComboBox* ComboBox, const QString& Namespace, const QString& VariableName);

    template <typename Transmit_Data>
    void TransmitMessageByTimer(EMessageTimer InMessageTimerType, Transmit_Data* CANData,
                                void (ACR_E11_Form::*Function)() = nullptr, uint delay = 1000, uint msec = 100);

    BYTE CAN_E2E_CalcuelateCRC8(BYTE Crc8_DataArray[], BYTE Crc8_Length);


    void SendGW740();

    void CreateItem(uint Id, QVector<BYTE> FilterData, std::function<void (const CANData&)> const & Func);

private slots:
    void On_WakeUp();

    //发送请求读取FBL版本
    void On_ReadVersion();

    void On_UnLock();

    void On_Polling();

    void On_CB_Polling1_CurrentIndexChanged(int index);
    void On_CB_Polling2_CurrentIndexChanged(int index);
    void On_CB_Polling3_CurrentIndexChanged(int index);
    void On_CB_Polling4_CurrentIndexChanged(int index);
    void On_CB_Polling5_CurrentIndexChanged(int index);

    void On_ACR_Req_LH_ComboBox_CurrentIndexChanged(int index);

private:
    void SetPollingUnit(DataDisplayWidget* DataDisplayWidget, int Value);

    //Req
private:
    void Send121(const CANData& Data);

    void ReqReadFBL();
    void ReqReadBSW_and_AnalyzingFBL(const CANData& Data);
    void AnalyzingBSW(const CANData& Data);

    void EnterExtendSession();
    void ReqSeed(const CANData& Data);
    void SendKey(const CANData& Data);
    void ReqUnlockECU(const CANData& Data);
    void ReqReadSV(const CANData& Data);
    void ReadSV_and_ReadState(const CANData& Data);

    void AnalyzingUnderlyingData(const CANData& Data);

private:
    Ui::ACR_E11_Form* ui;

    QVector<QReceiveItem*> Items;

    CHANNEL_HANDLE cHandle;


    MainWindow* mainWindow;

    BYTE CANE2E_CRC8_INITIALVALUE = 0xFF;
    BYTE CANE2E_CRC8_XORVALUE = 0xFF;
    BYTE CANE2E_CRC8_STARTVALUE = 0xFF;

    BYTE txDataBuffer_temp[7] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    BYTE cane2e_CrcTable8[256] =
    {
        0x00, 0x1D, 0x3A, 0x27, 0x74, 0x69, 0x4E, 0x53, 0xE8, 0xF5, 0xD2,
        0xCF, 0x9C, 0x81, 0xA6, 0xBB, 0xCD, 0xD0, 0xF7, 0xEA, 0xB9, 0xA4,
        0x83, 0x9E, 0x25, 0x38, 0x1F, 0x02, 0x51, 0x4C, 0x6B, 0x76, 0x87,
        0x9A, 0xBD, 0xA0, 0xF3, 0xEE, 0xC9, 0xD4, 0x6F, 0x72, 0x55, 0x48,
        0x1B, 0x06, 0x21, 0x3C, 0x4A, 0x57, 0x70, 0x6D, 0x3E, 0x23, 0x04,
        0x19, 0xA2, 0xBF, 0x98, 0x85, 0xD6, 0xCB, 0xEC, 0xF1, 0x13, 0x0E,
        0x29, 0x34, 0x67, 0x7A, 0x5D, 0x40, 0xFB, 0xE6, 0xC1, 0xDC, 0x8F,
        0x92, 0xB5, 0xA8, 0xDE, 0xC3, 0xE4, 0xF9, 0xAA, 0xB7, 0x90, 0x8D,
        0x36, 0x2B, 0x0C, 0x11, 0x42, 0x5F, 0x78, 0x65, 0x94, 0x89, 0xAE,
        0xB3, 0xE0, 0xFD, 0xDA, 0xC7, 0x7C, 0x61, 0x46, 0x5B, 0x08, 0x15,
        0x32, 0x2F, 0x59, 0x44, 0x63, 0x7E, 0x2D, 0x30, 0x17, 0x0A, 0xB1,
        0xAC, 0x8B, 0x96, 0xC5, 0xD8, 0xFF, 0xE2, 0x26, 0x3B, 0x1C, 0x01,
        0x52, 0x4F, 0x68, 0x75, 0xCE, 0xD3, 0xF4, 0xE9, 0xBA, 0xA7, 0x80,
        0x9D, 0xEB, 0xF6, 0xD1, 0xCC, 0x9F, 0x82, 0xA5, 0xB8, 0x03, 0x1E,
        0x39, 0x24, 0x77, 0x6A, 0x4D, 0x50, 0xA1, 0xBC, 0x9B, 0x86, 0xD5,
        0xC8, 0xEF, 0xF2, 0x49, 0x54, 0x73, 0x6E, 0x3D, 0x20, 0x07, 0x1A,
        0x6C, 0x71, 0x56, 0x4B, 0x18, 0x05, 0x22, 0x3F, 0x84, 0x99, 0xBE,
        0xA3, 0xF0, 0xED, 0xCA, 0xD7, 0x35, 0x28, 0x0F, 0x12, 0x41, 0x5C,
        0x7B, 0x66, 0xDD, 0xC0, 0xE7, 0xFA, 0xA9, 0xB4, 0x93, 0x8E, 0xF8,
        0xE5, 0xC2, 0xDF, 0x8C, 0x91, 0xB6, 0xAB, 0x10, 0x0D, 0x2A, 0x37,
        0x64, 0x79, 0x5E, 0x43, 0xB2, 0xAF, 0x88, 0x95, 0xC6, 0xDB, 0xFC,
        0xE1, 0x5A, 0x47, 0x60, 0x7D, 0x2E, 0x33, 0x14, 0x09, 0x7F, 0x62,
        0x45, 0x58, 0x0B, 0x16, 0x31, 0x2C, 0x97, 0x8A, 0xAD, 0xB0, 0xE3,
        0xFE, 0xD9, 0xC4
    };

    ZCAN_TransmitFD_Data canfd_data_406;
    ZCAN_TransmitFD_Data canfd_data_121;
    ZCAN_TransmitFD_Data canfd_data_1C2;
    ZCAN_TransmitFD_Data canfd_data_50;
    ZCAN_TransmitFD_Data canfd_data_288;
    ZCAN_TransmitFD_Data canfd_data_2D2;
    ZCAN_TransmitFD_Data canfd_data_2F7;
    ZCAN_TransmitFD_Data canfd_data_GW740;

    ZCAN_TransmitFD_Data canfd_data_PollingDataBuffer;

    int Count_121 = 0;
    int Count_GW740 = 0;

    //Variable
    QList<QComboBox*> CB_PollingDataComboBoxes;
};

template <typename Transmit_Data>
void ACR_E11_Form::TransmitMessageByTimer(EMessageTimer InMessageTimerType, Transmit_Data* CANData,
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
            // mainWindow->TransmitCANDataObj(CANData);

            ZCANCANFDData CANCANFDData{};
            CANCANFDData.flag.unionVal.frameType = 1;
            CANCANFDData.flag.unionVal.transmitType = 0;
            CANCANFDData.flag.unionVal.txDelay = ZCAN_TX_DELAY_NO_DELAY;
            CANCANFDData.flag.unionVal.txEchoed = 1;
            // CANCANFDData.frame = CANData->frame;

            ZCANDataObj DataObj{};
            DataObj.chnl = 0;
            DataObj.dataType = ZCAN_DT_ZCAN_CAN_CANFD_DATA;
            DataObj.data.zcanCANFDData = CANCANFDData;

            mainWindow->TransmitCANDataObj(&DataObj);

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

#endif // ACRFORM_H

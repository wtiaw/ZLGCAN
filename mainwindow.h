#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "CustomWidget/DataEdit.h"
#include "Setting/QDeviceSettingConfig.h"
#include "Windows/AutoSendConfigWindow.h"
#include "qdatetime.h"
#include "qlineedit.h"

enum FrameType
{
    CAN,
    CANFD,
};

enum DirectionType
{
    Transmit,
    Receive,
};

struct TableData
{
    qint64          ElapsedTime;
    canid_t         FrameID;
    FrameType       EventType;
    DirectionType   DirType;
    BYTE            DLC;
    QString         Data;
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    DEVICE_HANDLE GetDeviceHandle(){ return dhandle; }
    CHANNEL_HANDLE GetChannelHandle(){ return chHandle; }
    IProperty* GetProperty(){ return property; }

    int GetCanTypeFromUI();

public slots:
    void ReceiveData();
    void TransmitData();

    //MeaasgeTable
    void AddTableData(const ZCAN_Transmit_Data* data, UINT len);
    void AddTableData(const ZCAN_TransmitFD_Data* data, UINT len);

    //从面板获取CAN数据
    void GetViewCanFrame(ZCAN_Transmit_Data& can_data);
    void GetViewCanFrame(ZCAN_TransmitFD_Data& canfd_data);

private:
    void ReadConfig();

    //Init
    void Init();
    void InitButtonFunc();

    void InitDeviceNameComboBox();
    void InitDeviceIDComboBox();

    void InitChannelIDComboBox();
    void InitChannelWorkingModeComboBox();
    void InitChannelABitComboBox();
    void InitChannelDBitComboBox();
    void InitChannelResistanceComboBox();

    void InitMessageFrameTypeComboBox();
    void InitMessageTransmitTypeComboBox();

    void InitMessageTable();
    void ResetMessageTable();

    void InitMessageID();
    void InitMessageDLC();

    //Setting
    bool SetBaudRate();
    bool SetCANFDStandard();
    bool SetResistance();

    //MeaasgeTable
    void AddTableData(const ZCAN_Receive_Data* data, UINT len);
    void AddTableData(const ZCAN_ReceiveFD_Data* data, UINT len);
    void AddTableData(TableData& InTableData);

    //TransmitMeaasge
    void TransmitCAN();
    void TransmitCANFD();

    //检查DLC输入格式
    bool ChackDLCData();

    //根据 DLC 生成 Data输入格
    void CreateDataEdit();

    //获取Edit文本信息
    QString GetLineTextValue(const QLineEdit* InLineEdit);

    //获取DATA数据
    BYTE GetDataFromEdit(int Index);



private slots:
    //ButtonClick
    void On_OpenDevice();
    void On_InitCAN();
    void On_OpenCAN();
    void On_Reset();
    void On_CloseDevice();
    void On_SendMessage();
    void On_OpenAutoSendConfigWindow();

    //ComboBoxIndexChanged
    void On_ChannelIDChanged(int index);
    void On_WorkingModeChanged(int index);
    void On_ABitChanged(int index);
    void On_DBitChanged(int index);
    void On_ResistanceChanged(int index);
    void On_MessageFrameTypeChanged(int index);

    //LineEdit
    void On_DataIDChanged(const QString &arg1);
    void On_DLCChanged(const QString &arg1);



private:
    Ui::MainWindow *ui;
    AutoSendConfigWindow* AutoSendConfig;

    QDeviceSettingConfig* SettingConfig;

private:
    bool bInit = false;
    bool bIsRunThread = false;

    QVector<DataEdit*> DataEdits;

    QDateTime StartTime;

    DEVICE_HANDLE dhandle;
    CHANNEL_HANDLE chHandle;
    IProperty* property;

    class QReceiveThread*  ReceiveThread;
//    class QTransmitThread* TransmitThread;
};
#endif // MAINWINDOW_H

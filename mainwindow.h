#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "CustomWidget/DataEdit.h"
#include "CustomWidget/TableWidget/QMessageTableWidget.h"
#include "Setting/QDeviceSettingConfig.h"
#include "qlineedit.h"
#include "Library/QCANLibrary.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    DEVICE_HANDLE GetDeviceHandle() const { return dhandle; }
    CHANNEL_HANDLE GetChannelHandle() const { return chHandle; }
    IProperty* GetProperty(){ return property; }

    int GetCanTypeFromUI();

    //TransmitMeaasge
    void TransmitCAN(ZCAN_Transmit_Data can_data);
    void TransmitCANFD(ZCAN_TransmitFD_Data canfd_data);

    bool IsOpenCAN(){ return GetChannelHandle(); }

public slots:
    void ReceiveData();
    void TransmitData();

    //MeaasgeTable
    void AddTableData(const ZCAN_Transmit_Data* data, UINT len);
    void AddTableData(const ZCAN_TransmitFD_Data* data, UINT len);
    void AddTableData(const ZCAN_Receive_Data* data, UINT len);
    void AddTableData(const ZCAN_ReceiveFD_Data* data, UINT len);

    void AddTableData(const TableData& InTableData);

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


    int  AddTotalTableData(QMessageTableWidget* MessageTableWidget, const TableData& InTableData);
    void AddDeltaTableData(QMessageTableWidget* MessageTableWidget, const TableData& InTableData);
    int  AddDiagTableData(QMessageTableWidget* MessageTableWidget, const TableData& InTableData);



    //检查DLC输入格式
    bool ChackDLCData();

    //根据 DLC 生成 Data输入格
    void CreateDataEdit();

    //获取Edit文本信息
    QString GetLineTextValue(const QLineEdit* InLineEdit);

    //获取DATA数据
    BYTE GetDataFromEdit(int Index);

    void ConstructCANFrame(ZCAN_Transmit_Data& can_data);
    void ConstructCANFDFrame(ZCAN_TransmitFD_Data& can_data);

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

    //Timer
    void On_UpdateDeltaTableTableTimeOut();

    void On_AutoSendMessage();

    void On_MessageTableScrollPressed();
    void On_MessageTableScrollReleased();

    void on_ChangeTable_clicked(bool checked);

    void on_actionACR_triggered();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    class AutoSendConfigWindow* AutoSendConfig;
    class ACRForm* ACRFromWindow;

    QDeviceSettingConfig* SettingConfig;

private:
    bool bInit = false;
    bool bIsRunThread = false;
    bool bIsDragged = false;

    QVector<DataEdit*> DataEdits;
    QVector<QMessageTableWidget*> Tables;

    UINT64 RStartTime = 0;
    UINT64 TStartTime = 0;
    UINT64 temp = 0;

    DEVICE_HANDLE dhandle;
    CHANNEL_HANDLE chHandle;
    IProperty* property;

    class QReceiveThread*  ReceiveThread;

    class QTimer* UpdateDeltaTableTable;


};
#endif // MAINWINDOW_H

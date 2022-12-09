#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "CustomWidget/DataEdit.h"
#include "CustomWidget/TableWidget/QMessageTableWidget.h"
#include "Library/CircinalQueue.h"
#include "Setting/QDeviceSettingConfig.h"
#include "qlineedit.h"
#include "Library/QCANLibrary.h"
#include "binlog.h"
#include "Data/CustomEnum.h"
#include "Data/VariableStruct.h"
#include "Setting/QSystemVariables.h"
#include "Windows/Pannel/FormBase.h"


QT_BEGIN_NAMESPACE

namespace Ui
{
    class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

    [[nodiscard]] DEVICE_HANDLE GetDeviceHandle() const { return dHandle; }
    [[nodiscard]] CHANNEL_HANDLE GetChannelHandle() const { return chHandle; }
    [[nodiscard]] IProperty* GetProperty() const { return property; }

    [[nodiscard]] int GetCanTypeFromUI() const;

    [[nodiscard]] bool IsOpenCAN() const { return GetChannelHandle(); }

public slots:
    //TransmitMessage
    void TransmitCANDataObj(ZCANDataObj* DataObj);
    void TransmitCANDataObj(ZCAN_Transmit_Data& can_data);
    void TransmitCANDataObj(ZCAN_TransmitFD_Data& canfd_data);

    //MessageTable
    void AddTableData(const ZCANDataObj& DataObj);
    void AddTableData(const TableData& InTableData);

private:
    void ReadConfig();

    //Init
    void Init();
    void InitButtonFunc();

    void InitDeviceNameComboBox() const;
    void InitDeviceIDComboBox() const;

    void InitChannelIDComboBox() const;
    void InitChannelWorkingModeComboBox() const;
    void InitChannelABitComboBox() const;
    void InitChannelDBitComboBox() const;
    void InitChannelResistanceComboBox() const;

    void InitMessageFrameTypeComboBox() const;
    void InitMessageTransmitTypeComboBox() const;

    void InitMessageTable();
    void ResetMessageTable();

    void InitMessageID() const;
    void InitMessageDLC() const;

    void InitThread();

    //Setting
    [[nodiscard]] bool SetMerge() const;
    [[nodiscard]] bool SetBaudRate() const;
    [[nodiscard]] bool SetCANFDStandard() const;
    [[nodiscard]] bool SetResistance() const;
    [[nodiscard]] bool SetSendMode() const;

    //MessageTable
    int AddTotalTableData(QMessageTableWidget* MessageTableWidget, const TableData& InTableData);
    void AddDeltaTableData(QMessageTableWidget* MessageTableWidget, const TableData& InTableData);
    int AddDiagTableData(QMessageTableWidget* MessageTableWidget, const TableData& InTableData);

    //检查DLC输入格式
    bool CheckDLCData() const;

    //根据 DLC 生成 Data输入
    void CreateDataEdit();

    //获取Edit文本信息
    QString GetLineTextValue(const QLineEdit* InLineEdit);

    //获取DATA数据
    BYTE GetDataFromEdit(int Index);

    void ConstructCANFDData(ZCANCANFDData& CANFDData);
    void ConstructCANFrame(ZCAN_Transmit_Data& can_data);
    void ConstructCANFDFrame(ZCAN_TransmitFD_Data& can_data);

    //Log
    void CreateLogFile();
    void StopLogFile();
    void SaveSystemVariable(const ULONGLONG& time);

    void OpenFrom(CustomEnum::EFormType FormType);

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
    void On_DataIDChanged(const QString& arg1);
    void On_DLCChanged(const QString& arg1);

    //Timer
    void On_UpdateDeltaTableTableTimeOut();

    void On_AutoSendMessage();

    void On_MessageTableScrollPressed();
    void On_MessageTableScrollReleased();

    void on_ChangeTable_clicked(bool checked);


    void on_comboBox_currentIndexChanged(int index);

    void on_SaveLog_clicked(bool checked);

    void on_LoadVariables_triggered();

    void on_LoadDBC_triggered();

    //WindowAction
    void on_action_E11_triggered();
    void on_action_H53_triggered();

public:
    class QReceiveThread* ReceiveThread{};

    UINT64 StartTime = 0;

    static QSystemVariables* SystemVariablesConfig;

private:
    Ui::MainWindow* ui;
    class AutoSendConfigWindow* AutoSendConfig{};
    class ACR_E11_Form* ACR_E11_FromWindow = nullptr;
    class ACR_H53_Form* ACR_H53_FromWindow = nullptr;

    class LoadDBCWindow* LoadDbcWindowptr = nullptr;
    class LoadVariablesWindow* LoadVariablesWindowptr = nullptr;

    QDeviceSettingConfig* DeviceSettingConfig;

private:
    bool bInit = false;
    bool bIsRunThread = false;
    bool bIsDragged = false;
    bool bShouldSaveLog = false;
    bool bIsOpenCAN = false;

    QVector<DataEdit*> DataEdits;
    QVector<QMessageTableWidget*> Tables;
    QVector<TableData> DataLog;

    DEVICE_HANDLE dHandle{};
    CHANNEL_HANDLE chHandle{};
    IProperty* property{};

    class QTimer* UpdateDeltaTableTable;

    QString FilePath = QDir::currentPath() + tr("/log");

    HANDLE hFile = INVALID_HANDLE_VALUE;
    int CurrentDataCount = 0;
    int TotalDataCount = 0;

    CircinalQueue<VBLCANFDMessage_t>* MessageBuffer;

    //Form
    QMap<CustomEnum::EFormType, FormBase*> ActiveForms;
    CustomEnum::EFormType CurrentFromType = SystemVariablesConfig->GetCurrentType();
};
#endif // MAINWINDOW_H

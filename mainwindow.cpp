// ReSharper disable IdentifierTypo
#include "mainwindow.h"

#include <iostream>

#include "CustomWidget/DataEdit.h"
#include "Windows/ACRForm.h"
#include "Windows/AutoSendConfigWindow.h"
#include "ui_mainwindow.h"
#include "CustomThread/QReceiveThread.h"
#include "QTextCodec"
#include <QRegExp>
#include "QRegularExpressionValidator"
#include <QScrollBar>
#include <QStandardItemModel>
#include "Library/QWidgetLibrary.h"
#include <QtConcurrent>
#include <QtGlobal>
#include <QMessageBox>

#include "Windows/LoadDBCWindow.h"
#include "Windows/LoadVariablesWindow.h"


#define MAX_FILE_DATA_NUM 500000

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setAttribute(Qt::WA_QuitOnClose, true);

    ui->setupUi(this);

    UpdateDeltaTableTable = new QTimer;
    connect(UpdateDeltaTableTable, &QTimer::timeout, this, &MainWindow::On_UpdateDeltaTableTableTimeOut);

    Init();
    MessageBuffer = new CircinalQueue<VBLCANFDMessage_t>(400);
}

MainWindow::~MainWindow()
{
    delete ui;
    ReleaseIProperty(property);
    ZCAN_CloseDevice(dHandle);

    StopLogFile();
}

int MainWindow::GetCanTypeFromUI() const
{
    return ui->MessageFrameTypeComboBox->currentIndex();
}

void MainWindow::Init()
{
    dHandle = nullptr;
    chHandle = nullptr;

    InitButtonFunc();

    ReadConfig();

    InitDeviceNameComboBox();
    InitDeviceIDComboBox();

    InitChannelIDComboBox();
    InitChannelWorkingModeComboBox();
    InitChannelABitComboBox();
    InitChannelDBitComboBox();
    InitChannelResistanceComboBox();

    InitMessageFrameTypeComboBox();
    InitMessageTransmitTypeComboBox();

    InitMessageTable();

    InitMessageID();
    InitMessageDLC();

    InitThread();

    CreateDataEdit();

    bInit = true;
}

void MainWindow::InitButtonFunc()
{
    ui->InitCAN->       setEnabled(false);
    ui->OpenCAN->       setEnabled(false);
    ui->Reset->         setEnabled(false);
    ui->CloseDevice->   setEnabled(false);
    ui->Send->          setEnabled(false);


    //Button
    connect(ui->OpenDevice,     SIGNAL(clicked()), this, SLOT(On_OpenDevice()));
    connect(ui->InitCAN,        SIGNAL(clicked()), this, SLOT(On_InitCAN()));
    connect(ui->OpenCAN,        SIGNAL(clicked()), this, SLOT(On_OpenCAN()));
    connect(ui->Reset,          SIGNAL(clicked()), this, SLOT(On_Reset()));
    connect(ui->CloseDevice,    SIGNAL(clicked()), this, SLOT(On_CloseDevice()));
    connect(ui->Send,           SIGNAL(clicked()), this, SLOT(On_SendMessage()));
    connect(ui->ConfigAutoSend, SIGNAL(clicked()), this, SLOT(On_OpenAutoSendConfigWindow()));
    connect(ui->AutoSend,       SIGNAL(clicked()), this, SLOT(On_AutoSendMessage()));

    //ComboBox
    connect(ui->ChannelIDComboBox,        SIGNAL(currentIndexChanged(int)), this, SLOT(On_ChannelIDChanged(int)));
    connect(ui->WorkingModeComboBox,      SIGNAL(currentIndexChanged(int)), this, SLOT(On_WorkingModeChanged(int)));
    connect(ui->ABitComboBox,             SIGNAL(currentIndexChanged(int)), this, SLOT(On_ABitChanged(int)));
    connect(ui->DBitComboBox,             SIGNAL(currentIndexChanged(int)), this, SLOT(On_DBitChanged(int)));
    connect(ui->ResistanceComboBox,       SIGNAL(currentIndexChanged(int)), this, SLOT(On_ResistanceChanged(int)));
    connect(ui->MessageFrameTypeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(On_MessageFrameTypeChanged(int)));

    //Edit
    connect(ui->DataID,  SIGNAL(textChanged(const QString)), this, SLOT(On_DataIDChanged(const QString)));
    connect(ui->DLCEdit, SIGNAL(textChanged(const QString)), this, SLOT(On_DLCChanged(const QString)));

    for(const auto i : Tables){
        connect(i->verticalScrollBar(), SIGNAL(sliderPressed()),  this, SLOT(On_MessageTableScrollPressed()));
        connect(i->verticalScrollBar(), SIGNAL(sliderReleased()), this, SLOT(On_MessageTableScrollReleased()));
    }
}

void MainWindow::ReadConfig()
{
    DeviceSettingConfig = new QDeviceSettingConfig();
    DeviceSettingConfig->ReadConfig();

    SystemVariablesConfig = new QSystemVariables();
    SystemVariablesConfig->ReadConfig();
}

void MainWindow::InitDeviceNameComboBox() const
{
    ui->DeviceNameComboBox->addItem("USBCANFD");
}

void MainWindow::InitDeviceIDComboBox() const
{
    const int ConfigDevice = DeviceSettingConfig->GetDevice().ID;
    ui->DeviceIDCamboBox->setCurrentIndex(ConfigDevice);
}

void MainWindow::InitChannelIDComboBox() const
{
    const int ConfigDevice = DeviceSettingConfig->GetChannel().ID;
    ui->ChannelIDComboBox->setCurrentIndex(ConfigDevice);
}

void MainWindow::InitChannelWorkingModeComboBox() const
{
    ui->WorkingModeComboBox->clear();

    for (const auto& i : QDeviceSettingConfig::ChannelWorkingMode)
    {
        ui->WorkingModeComboBox->addItem(i.Display);
    }


    ui->DeviceNameComboBox->setCurrentIndex(DeviceSettingConfig->GetChannel().WorkingMode);
}

void MainWindow::InitChannelABitComboBox() const
{
    ui->ABitComboBox->clear();

    for (const auto& i : QDeviceSettingConfig::ChannelABitBaudRate)
    {
        ui->ABitComboBox->addItem(i.Display);
    }


    ui->ABitComboBox->setCurrentIndex(DeviceSettingConfig->GetChannel().ABitBaudRate);
}

void MainWindow::InitChannelDBitComboBox() const
{
    ui->DBitComboBox->clear();

    for (const auto& i : QDeviceSettingConfig::ChannelDBitBaudRate)
    {
        ui->DBitComboBox->addItem(i.Display);
    }


    ui->DBitComboBox->setCurrentIndex(DeviceSettingConfig->GetChannel().DBitBaudRate);
}

void MainWindow::InitChannelResistanceComboBox() const
{
    ui->ResistanceComboBox->clear();

    for (const auto& i : QDeviceSettingConfig::ChannelResistanceEnable)
    {
        ui->ResistanceComboBox->addItem(i.Display);
    }


    ui->ResistanceComboBox->setCurrentIndex(DeviceSettingConfig->GetChannel().Resistance);
}

void MainWindow::InitMessageFrameTypeComboBox() const
{
    ui->MessageFrameTypeComboBox->clear();

    for (const auto& i : QDeviceSettingConfig::MessageFrameType)
    {
        ui->MessageFrameTypeComboBox->addItem(i.Display);
    }


    ui->MessageFrameTypeComboBox->setCurrentIndex(0);
}

void MainWindow::InitMessageTransmitTypeComboBox() const
{
    ui->MessageTransmitComboBox->clear();

    for (const auto& i : QDeviceSettingConfig::MessageTransmitType)
    {
        ui->MessageTransmitComboBox->addItem(i.Display);
    }


    ui->MessageTransmitComboBox->setCurrentIndex(0);
}

void MainWindow::InitMessageTable()
{
    for (int i = 0; i < 3; i++)
    {
        const auto MessageTable = new QMessageTableWidget(this);
        Tables.append(MessageTable);

        ui->TableContainer->layout()->addWidget(MessageTable);

        if (i != 0)
        {
            MessageTable->hide();
        }
    }
}

void MainWindow::ResetMessageTable()
{
    for (const auto i : Tables)
    {
        while (i->rowCount())
        {
            i->removeRow(0);
        }

        i->MessageIDMap.clear();
    }
}

void MainWindow::InitMessageID() const
{
    QWidgetLibrary::InitMessageID(ui->DataID);
}

void MainWindow::InitMessageDLC() const
{
    QWidgetLibrary::InitMessageDLC(ui->DLCEdit);
}

void MainWindow::InitThread()
{
    ReceiveThread = new QReceiveThread(this);
}

bool MainWindow::SetMerge() const
{
    if (!property) return false;

    const SChannel ConfigChannel = DeviceSettingConfig->GetChannel();
    char path[50] = {0};
    sprintf_s(path, "%d/set_device_recv_merge", ConfigChannel.ID);
    
    return GetProperty()->SetValue(path, "1");
}

void MainWindow::On_OpenDevice()
{
    const auto [Name, ID] = DeviceSettingConfig->GetDevice();
    const std::string DeviceDisplayName = (QDeviceSettingConfig::DeviceName[Name].Display).toStdString();
    const int DeviceName = QDeviceSettingConfig::DeviceName[Name].Value;
    const int DeviceID = ID;

    TotalDataCount = 0;
    StartTime = 0;

    dHandle = ZCAN_OpenDevice(DeviceName, DeviceID, 0);
    if (nullptr == dHandle)
    {
        const QString ErrorMessage = QString("设备：%1 打开失败").arg(DeviceDisplayName.c_str());
        QMessageBox::critical(this,
                              tr("设备打开失败!"),
                              tr(ErrorMessage.toStdString().c_str())
        );
        return;
    }

    property = GetIProperty(dHandle);
    if (nullptr == property)
    {
        qDebug("设备：%s 打开失败!", (DeviceDisplayName.c_str()));
        return;
    }

    ResetMessageTable();


    ui->InitCAN->setEnabled(true);
    ui->CloseDevice->setEnabled(true);

    ui->OpenDevice->setEnabled(false);
    ui->DeviceNameComboBox->setEnabled(false);
    ui->DeviceIDCamboBox->setEnabled(false);

    qDebug("设备：%s 打开成功", (DeviceDisplayName.c_str()));

    if (ACRFromWindow) ACRFromWindow->InitWindow();
}

void MainWindow::On_InitCAN()
{
    std::string KeyStr;
    std::string ValueStr;

    if (!SetMerge())
    {
        qDebug("设置 合并接收模式 失败!");
        return;
    }
    
    if (!SetCANFDStandard())
    {
        qDebug("设置 CANFD标准 失败!");
        return;
    }

    if (!SetBaudRate())
    {
        qDebug("设置 波特率 失败!");
        return;
    }

    if (!SetResistance())
    {
        qDebug("设置 终端电阻 失败！");
        return;
    }

    auto [ID, WorkingMode, ABitBaudRate, DBitBaudRate, Resistance] = DeviceSettingConfig->GetChannel();
    ZCAN_CHANNEL_INIT_CONFIG cfg = {};
    cfg.can_type = TYPE_CANFD; //CANFD设备为TYPE_CANFD
    cfg.can.filter = 0;
    cfg.can.mode = QDeviceSettingConfig::ChannelWorkingMode[WorkingMode].Value; //正常模式, 1为只听模式
    cfg.can.acc_code = 0;
    cfg.can.acc_mask = 0xffffffff;
    chHandle = ZCAN_InitCAN(dHandle, ID, &cfg);
    if (nullptr == chHandle)
    {
        qDebug("初始化通道失败!");
        return;
    }

    qDebug("初始化通道成功!");
    char path[50] = {0};
    sprintf_s(path, "%d/set_device_recv_merge", ID);
    qDebug("合并模式：%s", property->GetValue(path));
    sprintf_s(path, "%d/canfd_abit_baud_rate", ID);
    qDebug("诊断域波特率：%s", property->GetValue(path));
    sprintf_s(path, "%d/canfd_dbit_baud_rate", ID);
    qDebug("数据域波特率：%s", property->GetValue(path));
    sprintf_s(path, "%d/initenal_resistance", ID);
    qDebug("终端电阻：%s", property->GetValue(path));


    ui->OpenCAN->setEnabled(true);

    ui->InitCAN->setEnabled(false);
    ui->ChannelIDComboBox->setEnabled(false);
    ui->WorkingModeComboBox->setEnabled(false);
    ui->ABitComboBox->setEnabled(false);
    ui->DBitComboBox->setEnabled(false);
    ui->ResistanceComboBox->setEnabled(false);
}

void MainWindow::On_OpenCAN()
{
    if (ZCAN_StartCAN(chHandle) != STATUS_OK)
    {
        qDebug("启动通道失败!");
        return;
    }

    if(!SetSendMode())
    {
        qDebug("设置 队列发送模式 失败!");
    }

    qDebug("启动通道成功");
    bIsOpenCAN = true;

    ui->Reset->setEnabled(true);
    ui->Send->setEnabled(true);
    ui->OpenCAN->setEnabled(false);

    if (bIsRunThread)
    {
        ReceiveThread->Resume();
    }
    else
    {
        ReceiveThread->start();

        bIsRunThread = true;
    }

    UpdateDeltaTableTable->start(10);
    
    if (bShouldSaveLog)
    {
        CreateLogFile();
    }
    
    ZCANDataObj CANDataObj;
    CANDataObj.dataType = ZCAN_DT_ZCAN_CAN_CANFD_DATA;
    CANDataObj.chnl = DeviceSettingConfig->GetChannel().ID;
    CANDataObj.data.zcanCANFDData.flag.unionVal.txEchoRequest = 0;

    ZCAN_TransmitData(chHandle, &CANDataObj, 1);
}

void MainWindow::On_Reset()
{
    ReleaseIProperty(property);
    chHandle = nullptr;

    qDebug("复位通道成功");
    bIsOpenCAN = false;

    ui->OpenCAN->setEnabled(true);

    ui->Reset->setEnabled(false);
    ui->Send->setEnabled(false);

    ReceiveThread->Pause();

    if (ACRFromWindow)
    {
        ACRFromWindow->StopTimer();
    }
}

void MainWindow::On_CloseDevice()
{
    ui->OpenDevice->setEnabled(true);
    ui->DeviceNameComboBox->setEnabled(true);
    ui->DeviceIDCamboBox->setEnabled(true);
    ui->ChannelIDComboBox->setEnabled(true);
    ui->WorkingModeComboBox->setEnabled(true);
    ui->ABitComboBox->setEnabled(true);
    ui->DBitComboBox->setEnabled(true);
    ui->ResistanceComboBox->setEnabled(true);

    ui->InitCAN->setEnabled(false);
    ui->OpenCAN->setEnabled(false);
    ui->Reset->setEnabled(false);
    ui->CloseDevice->setEnabled(false);
    ui->Send->setEnabled(false);

    ReceiveThread->Stop();
    bIsRunThread = false;

    bIsOpenCAN = false;

    ReleaseIProperty(property);
    ZCAN_CloseDevice(dHandle);
    dHandle = nullptr;

    const auto [Name, ID] = DeviceSettingConfig->GetDevice();
    const std::string DeviceDisplayName = (QDeviceSettingConfig::DeviceName[Name].Display).toStdString();
    qDebug("设备：%s 关闭!", (DeviceDisplayName.c_str()));

    UpdateDeltaTableTable->stop();
    if (ACRFromWindow)
    {
        ACRFromWindow->StopTimer();
    }

    StopLogFile();
}

void MainWindow::On_OpenAutoSendConfigWindow()
{
    if (!AutoSendConfig)
    {
        AutoSendConfig = new AutoSendConfigWindow();
        AutoSendConfig->setWindowTitle("配置自动发送报文");
    }

    AutoSendConfig->show();
}

void MainWindow::On_ChannelIDChanged(int index)
{
    if (!bInit) return;

    SChannel& ConfigChannel = DeviceSettingConfig->GetChannel();
    ConfigChannel.ID = index;

    DeviceSettingConfig->SaveConfig("Channel", "ChannelID", index);
}

void MainWindow::On_WorkingModeChanged(int index)
{
    if (!bInit) return;

    SChannel& ConfigChannel = DeviceSettingConfig->GetChannel();
    ConfigChannel.WorkingMode = index;

    DeviceSettingConfig->SaveConfig("Channel", "ChannelWorkingMode", index);
}

void MainWindow::On_ABitChanged(int index)
{
    if (!bInit) return;

    SChannel& ConfigChannel = DeviceSettingConfig->GetChannel();
    ConfigChannel.ABitBaudRate = index;

    DeviceSettingConfig->SaveConfig("Channel", "ChannelABitBaudRate", index);
}

void MainWindow::On_DBitChanged(int index)
{
    if (!bInit) return;

    SChannel& ConfigChannel = DeviceSettingConfig->GetChannel();
    ConfigChannel.DBitBaudRate = index;

    DeviceSettingConfig->SaveConfig("Channel", "ChannelDBitBaudRate", index);
}

void MainWindow::On_ResistanceChanged(int index)
{
    if (!bInit) return;

    SChannel& ConfigChannel = DeviceSettingConfig->GetChannel();
    ConfigChannel.Resistance = index;

    DeviceSettingConfig->SaveConfig("Channel", "ChannelResistance", index);
}

void MainWindow::On_MessageFrameTypeChanged(int index)
{
    QRegularExpression regx;
    if (index)
    {
        //CANFD
        regx = QRegularExpression("[0-9]{2}");
    }
    else
    {
        //CAN
        regx = QRegularExpression("[0-9]{1}");
    }

    const QValidator* validator = new QRegularExpressionValidator(regx, ui->DataID);
    ui->DLCEdit->setValidator(validator);
    CheckDLCData();
}

void MainWindow::On_DataIDChanged(const QString &arg1)
{
    ui->DataID->setText(arg1.toUpper());
}

void MainWindow::On_DLCChanged([[maybe_unused]] const QString &arg1)
{
    if (CheckDLCData() || ui->DLCEdit->text() == "")
    {
        CreateDataEdit();
    }
}

void MainWindow::On_UpdateDeltaTableTableTimeOut()
{
    if (!Tables[1]) return;

    for (auto& i : Tables[1]->MessageIDMap)
    {
        i.Count++;

        const int RowIndex = i.TableIndex;

        for (int j = 0; j < Tables[1]->columnCount() - 1; j++)
        {
            const int color = 0 + i.Count;
            Tables[1]->item(RowIndex, j)->setForeground(QColor(color, color, color, 255));
        }

        i.Count = i.Count >= 200 ? 200 : i.Count;
    }
}

void MainWindow::On_AutoSendMessage()
{
    ZCAN_AUTO_TRANSMIT_OBJ auto_can = {};

    auto_can.index = 0; 
    auto_can.enable = 1; 
    auto_can.interval = 100; 
    ConstructCANFrame(auto_can.obj); 


    GetProperty()->SetValue("0/auto_send", reinterpret_cast<const char*>(&auto_can));
    GetProperty()->SetValue("0/apply_auto_send", "0");
}

void MainWindow::On_MessageTableScrollPressed()
{
    bIsDragged = true;
}

void MainWindow::On_MessageTableScrollReleased()
{
    bIsDragged = false;
}

bool MainWindow::SetBaudRate() const
{
    if (!property) return false;

    const SChannel ConfigChannel = DeviceSettingConfig->GetChannel();
    char path[50] = {0};
    sprintf_s(path, "%d/canfd_abit_baud_rate", ConfigChannel.ID);
    char value[10] = {0};
    sprintf_s(value, "%d", QDeviceSettingConfig::ChannelABitBaudRate[ConfigChannel.ABitBaudRate].Value);
    int ret_a = property->SetValue(path, value);

    sprintf_s(path, "%d/canfd_dbit_baud_rate", ConfigChannel.ID);
    sprintf_s(value, "%d", QDeviceSettingConfig::ChannelDBitBaudRate[ConfigChannel.DBitBaudRate].Value);
    int ret_d = property->SetValue(path, value);
    return 1 == (ret_a && ret_d);
}

bool MainWindow::SetCANFDStandard() const
{
    SChannel ConfigChannel = DeviceSettingConfig->GetChannel();

    char path[50] = {0};
    sprintf_s(path, "%d/canfd_standard", ConfigChannel.ID);
    char value[10] = {0};
    sprintf_s(value, "%d", 0);
    return property->SetValue(path, value);
}

bool MainWindow::SetResistance() const
{
    const SChannel ConfigChannel = DeviceSettingConfig->GetChannel();

    //??????????
    char path[50] = {0};
    sprintf_s(path, "%d/initenal_resistance", ConfigChannel.ID);
    char value[10] = {0};
    sprintf_s(value, "%d", QDeviceSettingConfig::ChannelResistanceEnable[ConfigChannel.Resistance].Value);
    return property->SetValue(path, value);
}

bool MainWindow::SetSendMode() const
{
    const SChannel ConfigChannel = DeviceSettingConfig->GetChannel();
    
    char path[50] = {0};
    sprintf_s(path, "%d/set_send_mode", ConfigChannel.ID);
    
    return property->SetValue(path, "1"); 
}

void MainWindow::On_SendMessage()
{
    ZCANCANFDData CANFDData;
    ConstructCANFDData(CANFDData);

    ZCANDataObj CANDataObj;
    CANDataObj.dataType = ZCAN_DT_ZCAN_CAN_CANFD_DATA;
    CANDataObj.chnl = DeviceSettingConfig->GetChannel().ID;
    CANDataObj.data.zcanCANFDData = CANFDData;
    
    TransmitCANDataObj(&CANDataObj);
}

void MainWindow::AddTableData(const ZCANDataObj& DataObj)
{
    AddTableData(QCANLibrary::ConstructTableData(DataObj));
}

void MainWindow::AddTableData(const TableData& InTableData)
{
    AddTotalTableData(Tables[0], InTableData);
    AddDeltaTableData(Tables[1], InTableData);
    AddDiagTableData(Tables[2], InTableData);

    if (!bShouldSaveLog) return;

    // QFuture<void> future = QtConcurrent::run([=]()
    // {
        VBLCANFDMessage_t message = {};
        
        message.mHeader.mBase.mSignature = BL_OBJ_SIGNATURE;
        message.mHeader.mBase.mHeaderSize = sizeof(message.mHeader);
        message.mHeader.mBase.mHeaderVersion = 1;
        message.mHeader.mBase.mObjectSize = sizeof(VBLCANFDMessage_t);
        message.mHeader.mBase.mObjectType = BL_OBJ_TYPE_CAN_FD_MESSAGE;
        message.mHeader.mObjectFlags = BL_OBJ_FLAG_TIME_ONE_NANS;
        
        /* setup CAN object header */
        ULONGLONG time = (InTableData.TimeStamp - StartTime) * 1000;
        message.mHeader.mObjectTimeStamp = time;
        
        
        /* setup CAN message */
        message.mChannel = DeviceSettingConfig->GetChannel().ID + 1;
        message.mFlags = InTableData.DirType & 1;
        message.mDLC = InTableData.DLC;
        message.mValidDataBytes = InTableData.DLC;
        message.mID = InTableData.FrameID;
        message.mCANFDFlags = 1;
        for (int i = 0; i < InTableData.Data.length(); i++)
        {
            message.mData[i] = InTableData.Data[i];
        }
        
        int InsertIndex = MessageBuffer->GetLength() - 1;
        
        while (InsertIndex >= 0 && MessageBuffer->IndexAt(InsertIndex).mHeader.mObjectTimeStamp > time)
        {
            InsertIndex--;
        }
        MessageBuffer->Insert(InsertIndex + 1, message);
        
        int half = MessageBuffer->GetCapacity() / 2;
        if (hFile != INVALID_HANDLE_VALUE && MessageBuffer->GetLength() >= (half + half * 0.1))
        {
            for (int i = 0; i < half; i++)
            {
                VBLCANFDMessage_t temp;
                MessageBuffer->DeQueue(temp);
        
                const bool WriteSuccess = BLWriteObject(hFile, &temp.mHeader.mBase);
                CurrentDataCount += WriteSuccess;
                TotalDataCount += WriteSuccess;
            }
        }
    // });

    // qDebug() << "当前缓存数据:" << MessageBuffer->GetLength();
    // qDebug() << "当前文件数据:" << CurrentDataCount;
    // qDebug() << "总体文件数据:" << TotalDataCount;

    if (CurrentDataCount >= MAX_FILE_DATA_NUM)
    {
        StopLogFile();
        CreateLogFile();
    }
}

int MainWindow::AddTotalTableData(QMessageTableWidget *MessageTableWidget, const TableData &InTableData)
{

    const double CPUIntervalTime = (InTableData.TimeStamp - StartTime) / 1000000.0;
    int RowIndex = MessageTableWidget->rowCount(); //当前表格的行数

    while (MessageTableWidget->item(RowIndex - 1, 0) && MessageTableWidget->item(RowIndex - 1, 0)->text().toFloat() >
        CPUIntervalTime)
    {
        RowIndex--;
    }

    MessageTableWidget->insertRow(RowIndex);


    switch (InTableData.DirType)
    {
    case DirectionType::Receive:
        MessageTableWidget->setItem(RowIndex, 3, new QTableWidgetItem("Rx"));
        break;
    case DirectionType::Transmit:
        MessageTableWidget->setItem(RowIndex, 3, new QTableWidgetItem("Tx"));
        break;
    }
    MessageTableWidget->setItem(RowIndex, 0, new QTableWidgetItem(QString::number(CPUIntervalTime, 'f', 6)));
    MessageTableWidget->setItem(RowIndex, 1, new QTableWidgetItem(QString::number(InTableData.FrameID, 16).toUpper()));

    switch (InTableData.EventType)
    {
    case FrameType::CAN:
        MessageTableWidget->setItem(RowIndex, 2, new QTableWidgetItem("CAN"));
        break;
    case FrameType::CANFD:
        MessageTableWidget->setItem(RowIndex, 2, new QTableWidgetItem("CAN FD"));
        break;
    }

    MessageTableWidget->setItem(RowIndex, 4, new QTableWidgetItem(QString::number(InTableData.DLC)));

    QString str;
    for (const unsigned char i : InTableData.Data)
    {
        str += QString("%1 ").arg(i, 2, 16, QLatin1Char('0'));
    }
    MessageTableWidget->setItem(RowIndex, 5, new QTableWidgetItem(str.toUpper()));
    
    // if (MessageTableWidget->rowCount() >= 500)
    // {
    //     MessageTableWidget->removeRow(0);
    // }

    if (!bIsDragged && ui->EnableScroll->isChecked())
        MessageTableWidget->scrollToBottom();

    return RowIndex;
}

void MainWindow::AddDeltaTableData(QMessageTableWidget *MessageTableWidget, const TableData &InTableData)
{
    if (const auto& KeyInfo = MessageKeyInfo(InTableData.FrameID, InTableData.DirType); MessageTableWidget->MessageIDMap
        .contains(KeyInfo))
    {
        const int RowIndex = MessageTableWidget->MessageIDMap[KeyInfo].TableIndex;
        const UINT64 TimeStamp = MessageTableWidget->MessageIDMap[KeyInfo].intervalTimeNS;

        const double temp = InTableData.TimeStamp - TimeStamp;

        MessageTableWidget->setItem(RowIndex, 0,
                                    new QTableWidgetItem(QString::number(temp / 1000000.0, 'f', 6)));

        MessageTableWidget->MessageIDMap[KeyInfo].intervalTimeNS = InTableData.TimeStamp;


        QString str;
        for (const unsigned char i : InTableData.Data)
        {
            str += QString("%1 ").arg(i, 2, 16, QLatin1Char('0'));
        }
        MessageTableWidget->setItem(RowIndex, 5, new QTableWidgetItem(str.toUpper()));

        MessageTableWidget->MessageIDMap[KeyInfo].Count = 0;
    }
    else
    {
        const int RowIndex = AddTotalTableData(MessageTableWidget, InTableData);

        MessageTableWidget->MessageIDMap.insert(
            KeyInfo, MessageValueInfo(InTableData.TimeStamp, RowIndex, InTableData.CPUTime));
    }
}

int MainWindow::AddDiagTableData(QMessageTableWidget *MessageTableWidget, const TableData &InTableData)
{
    QByteArray ba;
    if (const uint ID = ba.setNum(InTableData.FrameID, 16).toUInt(nullptr, 16); (ID != 0x740) && (ID != 0x748))
    {
        return -1;
    }

    AddTotalTableData(MessageTableWidget, InTableData);

    return 0;
}

void MainWindow::TransmitCANDataObj(ZCANDataObj* DataObj)
{
    auto res = ZCAN_TransmitData(chHandle, DataObj, 1);
    // if(res)
    // {
    //     qDebug() << "成功发送报文" << QString::number(DataObj->data.zcanCANFDData.frame.can_id, 16);
    // }
}

void MainWindow::TransmitCANDataObj(ZCAN_Transmit_Data& can_data)
{
    ZCANDataObj DataObj;
    DataObj.chnl = DeviceSettingConfig->GetChannel().ID;
    DataObj.dataType = ZCAN_DT_ZCAN_CAN_CANFD_DATA;
    DataObj.data.zcanCANFDData.flag.unionVal.frameType = 0;
    DataObj.data.zcanCANFDData.flag.unionVal.transmitType = 0;
    DataObj.data.zcanCANFDData.flag.unionVal.txDelay =  ZCAN_TX_DELAY_NO_DELAY;
    DataObj.data.zcanCANFDData.flag.unionVal.txEchoed = 1;
    
    
    DataObj.data.zcanCANFDData.frame.can_id = can_data.frame.can_id;
    memcpy(&DataObj.data.zcanCANFDData.frame.data, &can_data.frame.data, 8);
    DataObj.data.zcanCANFDData.frame.len = can_data.frame.can_dlc;
    
    TransmitCANDataObj(&DataObj);
}

void MainWindow::TransmitCANDataObj(ZCAN_TransmitFD_Data& canfd_data)
{
    ZCANCANFDData CANCANFDData{};
    CANCANFDData.flag.unionVal.frameType = 1;
    CANCANFDData.flag.unionVal.transmitType = 0;
    CANCANFDData.flag.unionVal.txDelay = ZCAN_TX_DELAY_NO_DELAY;
    CANCANFDData.flag.unionVal.txEchoRequest = 1;
    CANCANFDData.frame = canfd_data.frame;
    
    ZCANDataObj DataObj{};
    DataObj.chnl = DeviceSettingConfig->GetChannel().ID;
    DataObj.dataType = ZCAN_DT_ZCAN_CAN_CANFD_DATA;
    DataObj.data.zcanCANFDData = CANCANFDData;

    TransmitCANDataObj(&DataObj);
}

bool MainWindow::CheckDLCData() const
{
    if (int tmp = ui->DLCEdit->text().toInt(); tmp < 0)
    {
        ui->DLCEdit->setText("0");
        return false;
    }
    else if (tmp > 8)
    {
        if (ui->MessageFrameTypeComboBox->currentIndex())
        {
            //CANFD
            if (tmp > 64)
            {
                ui->DLCEdit->setText("64");
                return false;
            }
        }
        else
        {
            //CAN
            ui->DLCEdit->setText("8");
            return false;
        }
    }

    return true;
}

void MainWindow::CreateDataEdit()
{
    QWidgetLibrary::CreateDataEdit(ui->DataContainer, ui->DLCEdit, DataEdits);
}

QString MainWindow::GetLineTextValue(const QLineEdit *InLineEdit)
{
    QString Result = InLineEdit->text();
    if (Result == "")
    {
        Result = InLineEdit->placeholderText();
    }

    return Result;
}

BYTE MainWindow::GetDataFromEdit(int Index)
{
    if (Index > DataEdits.length() - 1 || Index < 0)
    {
        return BYTE();
    }
    else
    {
        return DataEdits[Index]->text().toInt(nullptr, 16);
    }
}

void MainWindow::ConstructCANFDData(ZCANCANFDData& CANFDData)
{
    const canid_t CANID = GetLineTextValue(ui->DataID).toInt(nullptr, 16);
    const BYTE DLC = GetLineTextValue(ui->DLCEdit).toInt();
    const BYTE TransmitType = ui->MessageTransmitComboBox->currentIndex();

    memset(&CANFDData, 0, sizeof(CANFDData));
    CANFDData.frame.can_id = MAKE_CAN_ID(CANID, 0, 0, 0); // CAN ID
    CANFDData.frame.len = DLC; // CAN 数据长度
    CANFDData.flag.unionVal.transmitType = TransmitType; //发送模式
    CANFDData.flag.unionVal.txEchoRequest = 1;
    CANFDData.flag.unionVal.frameType = ui->MessageFrameTypeComboBox->currentIndex();
    CANFDData.flag.unionVal.txDelay = ZCAN_TX_DELAY_NO_DELAY;

    for (int i = 0; i < DLC; ++i)
    {
        CANFDData.frame.data[i] = GetDataFromEdit(i);
    }
}

void MainWindow::ConstructCANFrame(ZCAN_Transmit_Data &can_data)
{
    const canid_t CANID = GetLineTextValue(ui->DataID).toInt(nullptr, 16);
    const BYTE DLC = GetLineTextValue(ui->DLCEdit).toInt();
    const BYTE TransmitType = ui->MessageTransmitComboBox->currentIndex();

    memset(&can_data, 0, sizeof(can_data));
    can_data.frame.can_id = MAKE_CAN_ID(CANID, 0, 0, 0); // CAN ID
    can_data.frame.can_dlc = DLC; 
    can_data.transmit_type = TransmitType; 

    for (int i = 0; i < DLC; ++i)
    {
        can_data.frame.data[i] = GetDataFromEdit(i);
    }
}

void MainWindow::ConstructCANFDFrame(ZCAN_TransmitFD_Data& canfd_data)
{
    const canid_t CANID = GetLineTextValue(ui->DataID).toInt(nullptr, 16);
    const BYTE DLC = GetLineTextValue(ui->DLCEdit).toInt();
    const BYTE TransmitType = ui->MessageTransmitComboBox->currentIndex();

    memset(&canfd_data, 0, sizeof(canfd_data));
    canfd_data.frame.can_id = MAKE_CAN_ID(CANID, 0, 0, 0); // CANFD ID
    canfd_data.frame.len = DLC; 
    canfd_data.transmit_type = TransmitType;
    //    canfd_data.frame.flags    =  1;

    for (int i = 0; i < DLC; ++i)
    {
        canfd_data.frame.data[i] = GetDataFromEdit(i);
    }
}

void MainWindow::CreateLogFile()
{
    SYSTEMTIME systemTime;
    GetSystemTime(&systemTime);
    systemTime.wHour += 8;

    QString SystemTimestr = QString("LogFile_%1-%2-%3_%4-%5-%6")
                            .arg(QString::number(systemTime.wYear))
                            .arg(QString::number(systemTime.wMonth), 2, '0')
                            .arg(QString::number(systemTime.wDay), 2, '0')
                            .arg(QString::number(systemTime.wHour), 2, '0')
                            .arg(QString::number(systemTime.wMinute), 2, '0')
                            .arg(QString::number(systemTime.wSecond), 2, '0');

    const QString FileName = QString("%1/%2.blf").arg(FilePath, SystemTimestr);

    hFile = BLCreateFile((LPCSTR)(FileName).toLocal8Bit(), GENERIC_WRITE);

    if (INVALID_HANDLE_VALUE == hFile)
    {
        qDebug() << "Fall!";
        return;
    }

    bool bSuccess = BLSetApplication(hFile, BL_APPID_CANOE, 1, 0, 1);
    bSuccess = bSuccess && BLSetMeasurementStartTime(hFile, &systemTime);

    bSuccess = bSuccess && BLSetWriteOptions(hFile, 6, 0);
    qDebug() << "创建Log文件:" << FileName << bSuccess;
}

void MainWindow::StopLogFile()
{
    if (hFile != INVALID_HANDLE_VALUE)
    {
        for (int i = 0; i < MessageBuffer->GetLength(); i++)
        {
            VBLCANFDMessage_t temp;
            MessageBuffer->DeQueue(temp);

            const bool WriteSuccess = BLWriteObject(hFile, &temp.mHeader.mBase);
            CurrentDataCount += WriteSuccess;
            TotalDataCount += WriteSuccess;
        }

        qDebug() << "总体文件数据:" << TotalDataCount;


        qDebug() << "Close Log" << BLCloseHandle(hFile);
        hFile = INVALID_HANDLE_VALUE;

        CurrentDataCount = 0;
    }
}


void MainWindow::on_ChangeTable_clicked(bool checked)
{
    if (checked)
    {
        Tables[0]->hide();
        Tables[1]->show();
    }
    else
    {
        Tables[0]->show();
        Tables[1]->hide();
    }
}


void MainWindow::on_actionACR_triggered()
{
    if (!ACRFromWindow)
    {
        ACRFromWindow = new ACRForm(this, Qt::Window);
    }

    ACRFromWindow->show();
    ACRFromWindow->activateWindow();
}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    for (auto i : Tables)
    {
        i->hide();
    }

    Tables[index]->show();
}


void MainWindow::on_SaveLog_clicked(bool checked)
{
    bShouldSaveLog = checked;

    if (bShouldSaveLog)
    {
        if (const QDir dir(FilePath); !dir.exists())
        {
            if (const bool ismkdir = dir.mkdir(FilePath); !ismkdir)
                qDebug() << "Create path fail" << Qt::endl;
            else
                qDebug() << "Create fullpath success" << Qt::endl;
        }

        if (bIsOpenCAN) CreateLogFile();
    }
    else
    {
        StopLogFile();
    }
}


void MainWindow::on_LoadDBC_triggered()
{
    if(!LoadDbcWindowptr)
    {
        LoadDbcWindowptr = new LoadDBCWindow(this, Qt::Window);
    }
    
    LoadDbcWindowptr->show();
    LoadDbcWindowptr->activateWindow();
}

void MainWindow::on_LoadVariables_triggered()
{
    if(!LoadVariablesWindowptr)
    {
        LoadVariablesWindowptr = new LoadVariablesWindow(this, Qt::Window);
    }

    
    LoadVariablesWindowptr->show();
    LoadVariablesWindowptr->activateWindow();
}


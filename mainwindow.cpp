#include "mainwindow.h"
#include "CustomWidget/DataEdit.h"
#include "Windows/ACRForm.h"
#include "Windows/AutoSendConfigWindow.h"
#include "ui_mainwindow.h"
#include "CustomThread/QReceiveThread.h"
#include "QTextCodec"
#include <QRegExp>
#include "QRegularExpressionValidator"
#include <QDateTime>
#include <QSpacerItem>
#include <QScrollBar>
#include <QStandardItemModel>
#include "Library/QWidgetLibrary.h"

#define TMP_BUFFER_LEN 1000

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ReceiveThread = new QReceiveThread(this);

    UpdateDeltaTableTable = new QTimer;
    connect(UpdateDeltaTableTable, &QTimer::timeout,this, &MainWindow::On_UpdateDeltaTableTableTimeOut);

    Init();
}

MainWindow::~MainWindow()
{
    delete ui;

//    AutoSendConfig->exit();
//    delete AutoSendConfig;

    ReleaseIProperty(property);
    ZCAN_CloseDevice(dhandle);
}

int MainWindow::GetCanTypeFromUI()
{
    return ui->MessageFrameTypeComboBox->currentIndex();
}

void MainWindow::Init()
{
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

    connect(ui->AutoSend, SIGNAL(clicked()), this, SLOT(On_AutoSendMessage()));

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

    for(auto i : Tables){
        connect(i->verticalScrollBar(), SIGNAL(sliderPressed()),  this, SLOT(On_MessageTableScrollPressed()));
        connect(i->verticalScrollBar(), SIGNAL(sliderReleased()), this, SLOT(On_MessageTableScrollReleased()));
    }
}

void MainWindow::ReadConfig()
{
    SettingConfig = new class QDeviceSettingConfig;

    SettingConfig->ReadConfig();
}

void MainWindow::InitDeviceNameComboBox()
{
    QWidgetLibrary::InitMessageFrameTypeComboBox(ui->DeviceNameComboBox);
}

void MainWindow::InitDeviceIDComboBox()
{
    int ConfigDevice = SettingConfig->GetDevice().ID;
    ui->DeviceIDCamboBox->setCurrentIndex(ConfigDevice);
}

void MainWindow::InitChannelIDComboBox()
{
    int ConfigDevice = SettingConfig->GetChannel().ID;
    ui->ChannelIDComboBox->setCurrentIndex(ConfigDevice);
}

void MainWindow::InitChannelWorkingModeComboBox()
{
    ui->WorkingModeComboBox->clear();

    for (const auto &i : QDeviceSettingConfig::ChannelWorkingMode) {
        ui->WorkingModeComboBox->addItem(i.Display);
    }


    ui->DeviceNameComboBox->setCurrentIndex(SettingConfig->GetChannel().WorkingMode);
}

void MainWindow::InitChannelABitComboBox()
{
    ui->ABitComboBox->clear();

    for (const auto &i : QDeviceSettingConfig::ChannelABitBaudRate) {
        ui->ABitComboBox->addItem(i.Display);
    }


    ui->ABitComboBox->setCurrentIndex(SettingConfig->GetChannel().ABitBaudRate);
}

void MainWindow::InitChannelDBitComboBox()
{
    ui->DBitComboBox->clear();

    for (const auto &i : QDeviceSettingConfig::ChannelDBitBaudRate) {
        ui->DBitComboBox->addItem(i.Display);
    }


    ui->DBitComboBox->setCurrentIndex(SettingConfig->GetChannel().DBitBaudRate);
}

void MainWindow::InitChannelResistanceComboBox()
{
    ui->ResistanceComboBox->clear();

    for (const auto &i : QDeviceSettingConfig::ChannelResistanceEnable) {
        ui->ResistanceComboBox->addItem(i.Display);
    }


    ui->ResistanceComboBox->setCurrentIndex(SettingConfig->GetChannel().Resistance);
}

void MainWindow::InitMessageFrameTypeComboBox()
{
    ui->MessageFrameTypeComboBox->clear();

    for (const auto &i : QDeviceSettingConfig::MessageFrameType) {
        ui->MessageFrameTypeComboBox->addItem(i.Display);
    }


    ui->MessageFrameTypeComboBox->setCurrentIndex(0);
}

void MainWindow::InitMessageTransmitTypeComboBox()
{
    ui->MessageTransmitComboBox->clear();

    for (const auto &i : QDeviceSettingConfig::MessageTransmitType) {
        ui->MessageTransmitComboBox->addItem(i.Display);
    }


    ui->MessageTransmitComboBox->setCurrentIndex(0);
}

void MainWindow::InitMessageTable()
{
    for(int i = 0; i < 2; i++){
        QMessageTableWidget* MessageTable = new QMessageTableWidget(this);
        Tables.append(MessageTable);

        ui->TableContainer->layout()->addWidget(MessageTable);

        if(i == 1){
            MessageTable->hide();

            QStringList header;

            header<<"Time(ms)"<<"ID"<<"Type"<<"Dir"<<"DLC"<<"Data";
            MessageTable->setHorizontalHeaderLabels(header);
        }
    }
}

void MainWindow::ResetMessageTable()
{
    for(auto i :Tables){
        while(i->rowCount()){
            i->removeRow(0);
        }
    }
}

void MainWindow::InitMessageID()
{
    QWidgetLibrary::InitMessageID(ui->DataID);
}

void MainWindow::InitMessageDLC()
{
    QWidgetLibrary::InitMessageDLC(ui->DLCEdit);
}

void MainWindow::On_OpenDevice()
{
    SDevice ConfigDevice = SettingConfig->GetDevice();
    std::string DeviceDisplayName = (QDeviceSettingConfig::DeviceName[ConfigDevice.Name].Display).toStdString();
    int DeviceName = QDeviceSettingConfig::DeviceName[ConfigDevice.Name].Value;
    int DeviceID = ConfigDevice.ID;

    TStartTime = 0;
    RStartTime = 0;
    temp = 0;

    dhandle = ZCAN_OpenDevice(DeviceName, DeviceID, 0);
    if (INVALID_DEVICE_HANDLE == dhandle)
    {
        qDebug("设备：%s 打开失败",(DeviceDisplayName.c_str()));
        return;
    }

    property = GetIProperty(dhandle);
    if (NULL == property)
    {
        qDebug("设备：%s 打开失败",(DeviceDisplayName.c_str()));
        return;
    }

    ResetMessageTable();


    ui->InitCAN->      setEnabled(true);
    ui->CloseDevice->  setEnabled(true);

    ui->OpenDevice->          setEnabled(false);
    ui->DeviceNameComboBox->  setEnabled(false);
    ui->DeviceIDCamboBox->    setEnabled(false);

    qDebug("设备：%s 打开成功",(DeviceDisplayName.c_str()));
}

void MainWindow::On_InitCAN()
{
    std::string keystr;
    std::string valuestr;

    if (!SetCANFDStandard()) {
        qDebug("设置 CANFD标准 失败!");
        return;
    }

    if(!SetBaudRate()){
        qDebug("设置 波特率 失败!");
        return;
    }

    if(!SetResistance())
    {
        qDebug("设置 终端电阻 失败！");
        return;
    }

    SChannel ConfigChannel = SettingConfig->GetChannel();
    ZCAN_CHANNEL_INIT_CONFIG cfg;
    memset(&cfg, 0, sizeof(cfg));
    cfg.can_type = TYPE_CANFD;  //CANFD设备为TYPE_CANFD
    cfg.can.filter = 0;
    cfg.can.mode = QDeviceSettingConfig::ChannelWorkingMode[ConfigChannel.WorkingMode].Value; //正常模式, 1为只听模式
    cfg.can.acc_code = 0;
    cfg.can.acc_mask = 0xffffffff;
    chHandle = ZCAN_InitCAN(dhandle, ConfigChannel.ID, &cfg);
    if (INVALID_CHANNEL_HANDLE == chHandle)
    {
        qDebug("初始化通道失败");
        return;
    }

    qDebug("初始化通道成功");
    char path[50] = { 0 };
    sprintf_s(path, "%d/canfd_abit_baud_rate", ConfigChannel.ID);
    qDebug("诊断域波特率：%s",property->GetValue(path));
    sprintf_s(path, "%d/canfd_dbit_baud_rate", ConfigChannel.ID);
    qDebug("数据域波特率：%s",property->GetValue(path));
    sprintf_s(path, "%d/initenal_resistance", ConfigChannel.ID);
    qDebug("终端电阻：%s",property->GetValue(path));


    ui->OpenCAN->              setEnabled(true);

    ui->InitCAN->              setEnabled(false);
    ui->ChannelIDComboBox->    setEnabled(false);
    ui->WorkingModeComboBox->  setEnabled(false);
    ui->ABitComboBox->         setEnabled(false);
    ui->DBitComboBox->         setEnabled(false);
    ui->ResistanceComboBox->   setEnabled(false);

//    property->SetValue("0/filter_mode", "0"); // 标准帧
//    property->SetValue("0/filter_start", "0x740");  // 起始 ID
//    property->SetValue("0/filter_end", "0x748");  // 结束 ID
//    property->SetValue("0/filter_ack", "0");
}

void MainWindow::On_OpenCAN()
{
    if (ZCAN_StartCAN(chHandle) != STATUS_OK)
    {
        qDebug("启动通道失败");
        return;
    }

    qDebug("启动通道成功");

    ui->Reset->    setEnabled(true);
    ui->Send->     setEnabled(true);

    ui->OpenCAN->  setEnabled(false);

    if(bIsRunThread)
    {
        ReceiveThread->Resume();
    }
    else
    {
        ReceiveThread->start();

        bIsRunThread = true;
    }

    UpdateDeltaTableTable->start(10);
}

void MainWindow::On_Reset()
{
    ReleaseIProperty(property);

    qDebug("复位通道成功");
    ui->OpenCAN->  setEnabled(true);

    ui->Reset->    setEnabled(false);
    ui->Send->     setEnabled(false);

    ReceiveThread->Pause();
}

void MainWindow::On_CloseDevice()
{
    ui->OpenDevice->           setEnabled(true);
    ui->DeviceNameComboBox->   setEnabled(true);
    ui->DeviceIDCamboBox->     setEnabled(true);
    ui->ChannelIDComboBox->    setEnabled(true);
    ui->WorkingModeComboBox->  setEnabled(true);
    ui->ABitComboBox->         setEnabled(true);
    ui->DBitComboBox->         setEnabled(true);
    ui->ResistanceComboBox->   setEnabled(true);

    ui->InitCAN->              setEnabled(false);
    ui->OpenCAN->              setEnabled(false);
    ui->Reset->                setEnabled(false);
    ui->CloseDevice->          setEnabled(false);
    ui->Send->                 setEnabled(false);

    ReceiveThread->Stop();
    bIsRunThread = false;

    ReleaseIProperty(property);
    ZCAN_CloseDevice(dhandle);

    SDevice ConfigDevice = SettingConfig->GetDevice();
    std::string DeviceDisplayName = (QDeviceSettingConfig::DeviceName[ConfigDevice.Name].Display).toStdString();
    qDebug("设备：%s 关闭",(DeviceDisplayName.c_str()));

    UpdateDeltaTableTable->stop();
}

void MainWindow::On_OpenAutoSendConfigWindow()
{
    if(!AutoSendConfig){
        AutoSendConfig = new AutoSendConfigWindow();
        AutoSendConfig->setWindowTitle("配置自动发送报文");
    }

    AutoSendConfig->show();
}

void MainWindow::On_ChannelIDChanged(int index)
{
    if(!bInit) return;

    SChannel& ConfigChannel = SettingConfig->GetChannel();
    ConfigChannel.ID = index;

    SettingConfig->SaveConfig(ChannelIDPath, index);
}

void MainWindow::On_WorkingModeChanged(int index)
{
    if(!bInit) return;

    SChannel& ConfigChannel = SettingConfig->GetChannel();
    ConfigChannel.WorkingMode = index;

    SettingConfig->SaveConfig(ChannelWorkingModePath, index);
}

void MainWindow::On_ABitChanged(int index)
{
    if(!bInit) return;

    SChannel& ConfigChannel = SettingConfig->GetChannel();
    ConfigChannel.ABitBaudRate = index;

    SettingConfig->SaveConfig(ChannelABitBaudRatePath, index);
}

void MainWindow::On_DBitChanged(int index)
{
    if(!bInit) return;

    SChannel& ConfigChannel = SettingConfig->GetChannel();
    ConfigChannel.DBitBaudRate = index;

    SettingConfig->SaveConfig(ChannelDBitBaudRatePath, index);
}

void MainWindow::On_ResistanceChanged(int index)
{
    if(!bInit) return;

    SChannel& ConfigChannel = SettingConfig->GetChannel();
    ConfigChannel.Resistance = index;

    SettingConfig->SaveConfig(ChannelResistancePath, index);
}

void MainWindow::On_MessageFrameTypeChanged(int index)
{
    QRegularExpression regx;
    if(index){
        //CANFD
        regx = QRegularExpression("[0-9]{2}");
    }
    else
    {
        //CAN
        regx = QRegularExpression("[0-9]{1}");
    }

    QValidator* validator = new QRegularExpressionValidator(regx, ui->DataID);
    ui->DLCEdit->setValidator(validator);
    ChackDLCData();
}

void MainWindow::On_DataIDChanged(const QString &arg1)
{
    ui->DataID->setText(arg1.toUpper());
}

void MainWindow::On_DLCChanged(const QString &arg1)
{
    if(ChackDLCData() || ui->DLCEdit->text() == "")
    {
        CreateDataEdit();
    }
}

void MainWindow::On_UpdateDeltaTableTableTimeOut()
{
    if(!Tables[1]) return;

    for(auto& i : Tables[1]->MessageIDMap){
        i.Count++;

        int rowIndex  = i.TableIndex;

        for(int j = 0; j < Tables[1]->columnCount() - 1; j++){
            int color = 0 + i.Count;
            Tables[1]->item(rowIndex, j)->setForeground(QColor(color, color, color, 255));
        }

        i.Count = i.Count >= 200 ? 200 : i.Count;
    }
}

void MainWindow::On_AutoSendMessage()
{
    ZCAN_AUTO_TRANSMIT_OBJ auto_can;

    memset(&auto_can, 0, sizeof(auto_can));
    auto_can.index = 0;  // 定时列表索引 0
    auto_can.enable = 1; // 使能此索引，每条可单独设置
    auto_can.interval = 700;  // 定时发送间隔 100ms
    ConstructCANFrame(auto_can.obj); // 构造 CAN 报文

//    ZCAN_AUTO_TRANSMIT_OBJ auto_can1;

//    memset(&auto_can1, 0, sizeof(auto_can1));
//    auto_can1.index = 1;  // 定时列表索引 0
//    auto_can1.enable = 1; // 使能此索引，每条可单独设置
//    auto_can1.interval = 700;  // 定时发送间隔 100ms
//    ConstructCANFrame(auto_can1.obj); // 构造 CAN 报文
//    auto_can1.obj.transmit_type = 2;

    GetProperty()->SetValue("0/auto_send", (const char*)&auto_can);
//    GetProperty()->SetValue("0/auto_send", (const char*)&auto_can1);
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

bool MainWindow::SetBaudRate()
{
    if (!property) return false;

    SChannel ConfigChannel = SettingConfig->GetChannel();
    char path[50] = { 0 };
    sprintf_s(path, "%d/canfd_abit_baud_rate", ConfigChannel.ID);
    char value[10] = { 0 };
    sprintf_s(value, "%d", QDeviceSettingConfig::ChannelABitBaudRate[ConfigChannel.ABitBaudRate].Value);
    int ret_a = property->SetValue(path, value);

    sprintf_s(path, "%d/canfd_dbit_baud_rate", ConfigChannel.ID);
    sprintf_s(value, "%d", QDeviceSettingConfig::ChannelDBitBaudRate[ConfigChannel.DBitBaudRate].Value);
    int ret_d = property->SetValue(path, value);
    return 1 == (ret_a&&ret_d);
}

bool MainWindow::SetCANFDStandard()
{
    SChannel ConfigChannel = SettingConfig->GetChannel();

    char path[50] = { 0 };
    sprintf_s(path, "%d/canfd_standard", ConfigChannel.ID);
    char value[10] = { 0 };
    sprintf_s(value, "%d", 0);
    return property->SetValue(path, value);;
}

bool MainWindow::SetResistance()
{
    SChannel ConfigChannel = SettingConfig->GetChannel();

    //设置终端电阻
    char path[50] = { 0 };
    sprintf_s(path, "%d/initenal_resistance", ConfigChannel.ID);
    char value[10] = { 0 };
    sprintf_s(value, "%d", QDeviceSettingConfig::ChannelResistanceEnable[ConfigChannel.Resistance].Value);
    return property->SetValue(path, value);
}

void MainWindow::On_SendMessage()
{
//    QTransmitThread* TransmitThread = new QTransmitThread(this);
//    TransmitThread->start();
    TransmitData();
}

void MainWindow::ReceiveData()
{
    ZCAN_Receive_Data can_data[100];
    ZCAN_ReceiveFD_Data canfd_data[100];
    UINT len;

    if (len = ZCAN_GetReceiveNum(chHandle, TYPE_CAN))
    {
        len = ZCAN_Receive(chHandle, can_data, 100, 10);

        AddTableData(can_data, len);
    }
    if (len = ZCAN_GetReceiveNum(chHandle, TYPE_CANFD))
    {
        len = ZCAN_ReceiveFD(chHandle, canfd_data, 100, 10);
        AddTableData(canfd_data, len);
    }
}

void MainWindow::TransmitData()
{
    switch (ui->MessageFrameTypeComboBox->currentIndex()) {
    case 0:
        TransmitCAN();
        break;
    case 1:
        TransmitCANFD();
        break;
    }
}

void MainWindow::AddTableData(const ZCAN_Receive_Data *data, UINT len)
{
    for (UINT i = 0; i < len; ++i)
    {
        const ZCAN_Receive_Data& can = data[i];
        const canid_t& id = can.frame.can_id;
        QString str;

        TableData InTableData;
        InTableData.TimeStamp    =   can.timestamp;
        InTableData.FrameID      =   GET_ID(id);
        InTableData.EventType    =   FrameType::CAN;
        InTableData.DirType      =   DirectionType::Receive;
        InTableData.DLC          =   can.frame.can_dlc;

        for (UINT i = 0; i < can.frame.can_dlc; ++i)
        {
            str += QString("%1 ").arg(can.frame.data[i], 2, 16, QLatin1Char('0'));
        }

        InTableData.Data = str.toUpper();

        AddTableData(InTableData);
    }
}

void MainWindow::AddTableData(const ZCAN_ReceiveFD_Data *data, UINT len)
{
    for (UINT i = 0; i < len; ++i)
    {
        const ZCAN_ReceiveFD_Data& canfd = data[i];
        const canid_t& id = canfd.frame.can_id;
        QString str;

        TableData InTableData;
        InTableData.TimeStamp    =   canfd.timestamp;
        InTableData.FrameID      =   GET_ID(id);
        InTableData.EventType    =   FrameType::CANFD;
        InTableData.DirType      =   DirectionType::Receive;
        InTableData.DLC          =   canfd.frame.len;

        for (UINT i = 0; i < canfd.frame.len; ++i)
        {

            str += QString("%1 ").arg(canfd.frame.data[i], 2, 16, QLatin1Char('0'));
        }

        InTableData.Data = str.toUpper();

        AddTableData(InTableData);
    }
}

void MainWindow::AddTableData(const ZCAN_Transmit_Data *data, UINT len)
{

    for (UINT i = 0; i < len; ++i)
    {
        const ZCAN_Transmit_Data& can = data[i];
        const canid_t& id = can.frame.can_id;
        QString str;

        TableData InTableData;
        InTableData.TimeStamp    =   QDateTime::currentMSecsSinceEpoch();
        InTableData.FrameID      =   GET_ID(id);
        InTableData.EventType    =   FrameType::CAN;
        InTableData.DirType      =   DirectionType::Transmit;
        InTableData.DLC          =   can.frame.can_dlc;

        for (UINT i = 0; i < can.frame.can_dlc; ++i)
        {
            str += QString("%1 ").arg(can.frame.data[i],2,16,QLatin1Char('0'));
        }

        InTableData.Data = str.toUpper();

        AddTableData(InTableData);
    }
}

void MainWindow::AddTableData(const ZCAN_TransmitFD_Data *data, UINT len)
{
    for (UINT i = 0; i < len; ++i)
    {
        const ZCAN_TransmitFD_Data& canfd = data[i];
        const canid_t& id = canfd.frame.can_id;
        QString str;

        TableData InTableData;
        InTableData.TimeStamp    =   QDateTime::currentMSecsSinceEpoch();
        InTableData.FrameID      =   GET_ID(id);
        InTableData.EventType    =   FrameType::CANFD;
        InTableData.DirType      =   DirectionType::Transmit;
        InTableData.DLC          =   canfd.frame.len;

        for (UINT i = 0; i < canfd.frame.len; ++i)
        {
            str += QString("%1 ").arg(canfd.frame.data[i],2,16,QLatin1Char('0'));
        }

        InTableData.Data = str.toUpper();

        AddTableData(InTableData);
    }
}

void MainWindow::AddTableData(TableData& InTableData)
{
    AddTotalTablData(Tables[0], InTableData);
    AddDeltaTablData(Tables[1], InTableData);
}

int MainWindow::AddTotalTablData(QMessageTableWidget *MessageTableWidget, TableData &InTableData)
{
    int rowIndex = MessageTableWidget->rowCount();//当前表格的行数
    MessageTableWidget->insertRow(rowIndex);//在最后一行的后面插入一行

    UINT64 intervalTimeMS;
    switch (InTableData.DirType) {
    case DirectionType::Receive:
        MessageTableWidget->setItem(rowIndex, 3, new QTableWidgetItem("Rx"));

        if(RStartTime == 0)
        {
            RStartTime = InTableData.TimeStamp;


            temp = TStartTime ? QDateTime::currentMSecsSinceEpoch() - TStartTime : 0;
        }
        intervalTimeMS = InTableData.TimeStamp - RStartTime;
        intervalTimeMS /= 1000.0;
        intervalTimeMS += temp;

        break;
    case DirectionType::Transmit:
        MessageTableWidget->setItem(rowIndex, 3, new QTableWidgetItem("Tx"));

        if(TStartTime == 0)
        {
            TStartTime = InTableData.TimeStamp;
        }

        intervalTimeMS = InTableData.TimeStamp - TStartTime;

        break;
    }


    MessageTableWidget->setItem(rowIndex, 0, new QTableWidgetItem(QString::number(intervalTimeMS/1000.0, 'f', 3)));
    MessageTableWidget->setItem(rowIndex, 1, new QTableWidgetItem(QString::number(InTableData.FrameID, 16).toUpper()));

    switch (InTableData.EventType) {
    case FrameType::CAN:
        MessageTableWidget->setItem(rowIndex, 2, new QTableWidgetItem("CAN"));
        break;
    case FrameType::CANFD:
        MessageTableWidget->setItem(rowIndex, 2, new QTableWidgetItem("CAN FD"));
        break;
    }

    MessageTableWidget->setItem(rowIndex, 4, new QTableWidgetItem(QString::number(InTableData.DLC)));
    MessageTableWidget->setItem(rowIndex, 5, new QTableWidgetItem(InTableData.Data));

    if(!bIsDragged && ui->EnableScroll->isChecked())
        MessageTableWidget->scrollToBottom();

    return rowIndex;
}

void MainWindow::AddDeltaTablData(QMessageTableWidget *MessageTableWidget, TableData &InTableData)
{
    const MessageKeyInfo& KeyInfo = MessageKeyInfo(InTableData.FrameID, InTableData.DirType);

    if(MessageTableWidget->MessageIDMap.contains(KeyInfo))
    {
        int rowIndex  = MessageTableWidget->MessageIDMap[KeyInfo].TableIndex;
        UINT64 TimeStamp = MessageTableWidget->MessageIDMap[KeyInfo].intervalTimeMS;

        double temp = InTableData.TimeStamp - TimeStamp;
        MessageTableWidget->item(rowIndex, 0)->setText(QString::number(temp/(KeyInfo.directionType == DirectionType::Transmit ? 1 : 1000),'f', 2));
        MessageTableWidget->item(rowIndex, 5)->setText(InTableData.Data);

        MessageTableWidget->MessageIDMap[KeyInfo].intervalTimeMS = InTableData.TimeStamp;
        MessageTableWidget->MessageIDMap[KeyInfo].Count = 0;
    }
    else
    {
        int rowIndex = AddTotalTablData(MessageTableWidget, InTableData);

        MessageTableWidget->MessageIDMap.insert(KeyInfo, MessageValueInfo(InTableData.TimeStamp, rowIndex));
    }
}

void MainWindow::TransmitCAN()
{
    ZCAN_Transmit_Data can_data;

    ConstructCANFrame(can_data);

    auto result = ZCAN_Transmit(chHandle, &can_data, 1);
//    if(can_data.transmit_type != 2){
       AddTableData(&can_data,1);
//    }
}

void MainWindow::TransmitCANFD()
{
    ZCAN_TransmitFD_Data canfd_data;

    ConstructCANFDFrame(canfd_data);

    auto result = ZCAN_TransmitFD(chHandle, &canfd_data, 1);
//    if(canfd_data.transmit_type != 2){
        AddTableData(&canfd_data,1);
//    }
}

bool MainWindow::ChackDLCData()
{
    int tmp = ui->DLCEdit->text().toInt();

    if(tmp < 0)
    {
        ui->DLCEdit->setText("0");
        return false;
    }
    else if(tmp > 8)
    {
        if(ui->MessageFrameTypeComboBox->currentIndex())
        {
            //CANFD
            if(tmp > 64)
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
    if(Result == ""){
        Result = InLineEdit->placeholderText();
    }

    return Result;
}

BYTE MainWindow::GetDataFromEdit(int Index)
{
    if(Index > DataEdits.length() -1 || Index < 0){
        return BYTE();
    }
    else
    {
        return DataEdits[Index]->text().toInt(nullptr, 16);
    }
}

void MainWindow::ConstructCANFrame(ZCAN_Transmit_Data &can_data)
{
    canid_t CANID     = GetLineTextValue(ui->DataID).toInt(nullptr ,16);
    BYTE DLC          = GetLineTextValue(ui->DLCEdit).toInt();
    BYTE TransmitType = ui->MessageTransmitComboBox->currentIndex();

    memset(&can_data, 0, sizeof(can_data));
    can_data.frame.can_id   =  MAKE_CAN_ID(CANID, 0, 0, 0);         // CAN ID
    can_data.frame.can_dlc  =  DLC;                                 // CAN 数据长度
    can_data.transmit_type  =  TransmitType;                        //发送模式

    for (int i = 0; i < DLC; ++i)
    {
        can_data.frame.data[i] = GetDataFromEdit(i);
    }
}

void MainWindow::ConstructCANFDFrame(ZCAN_TransmitFD_Data& canfd_data)
{
    canid_t CANID = GetLineTextValue(ui->DataID).toInt(nullptr, 16);
    BYTE DLC = GetLineTextValue(ui->DLCEdit).toInt();
    BYTE TransmitType = ui->MessageTransmitComboBox->currentIndex();

    memset(&canfd_data, 0, sizeof(canfd_data));
    canfd_data.frame.can_id   =  MAKE_CAN_ID(CANID, 0, 0, 0);    // CANFD ID
    canfd_data.frame.len      =  DLC;                            // CANFD 数据长度
    canfd_data.transmit_type  =  TransmitType;
//    canfd_data.frame.flags    =  1;

    for (int i = 0; i < DLC; ++i)
    {
        canfd_data.frame.data[i] = GetDataFromEdit(i);
    }
}


void MainWindow::on_ChangeTable_clicked(bool checked)
{
    if(checked)
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
    if(!ACRFromWindow)
        ACRFromWindow = new ACRForm;

    ACRFromWindow->show();
}


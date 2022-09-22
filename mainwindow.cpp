#include "mainwindow.h"
#include "CustomWidget/DataEdit.h"
#include "ui_mainwindow.h"
#include "QTextCodec"
#include "ReceiveDataThread.h"
#include <QRegExp>
#include "QRegularExpressionValidator"
#include <QDateTime>
#include <QSpacerItem>

#define TMP_BUFFER_LEN 1000

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ReceiveThread = new ReceiveDataThread(this);

    Init();
}

MainWindow::~MainWindow()
{
    delete ui;

    ReleaseIProperty(property);
    ZCAN_CloseDevice(dhandle);
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
    connect(ui->OpenDevice,  SIGNAL(clicked()), this, SLOT(On_OpenDevice()));
    connect(ui->InitCAN,     SIGNAL(clicked()), this, SLOT(On_InitCAN()));
    connect(ui->OpenCAN,     SIGNAL(clicked()), this, SLOT(On_OpenCAN()));
    connect(ui->Reset,       SIGNAL(clicked()), this, SLOT(On_Reset()));
    connect(ui->CloseDevice, SIGNAL(clicked()), this, SLOT(On_CloseDevice()));
    connect(ui->Send,        SIGNAL(clicked()), this, SLOT(On_SendMessage()));

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
}

void MainWindow::ReadConfig()
{
    SettingConfig = new class SettingConfig;

    SettingConfig->ReadConfig();
}

void MainWindow::InitDeviceNameComboBox()
{
    ui->DeviceNameComboBox->clear();

    for (const auto &i : SettingConfig::DeviceName) {
        ui->DeviceNameComboBox->addItem(i.Display);
    }

    ui->DeviceNameComboBox->setCurrentIndex(SettingConfig->GetDevice().Name);
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

    for (const auto &i : SettingConfig::ChannelWorkingMode) {
        ui->WorkingModeComboBox->addItem(i.Display);
    }


    ui->DeviceNameComboBox->setCurrentIndex(SettingConfig->GetChannel().WorkingMode);
}

void MainWindow::InitChannelABitComboBox()
{
    ui->ABitComboBox->clear();

    for (const auto &i : SettingConfig::ChannelABitBaudRate) {
        ui->ABitComboBox->addItem(i.Display);
    }


    ui->ABitComboBox->setCurrentIndex(SettingConfig->GetChannel().ABitBaudRate);
}

void MainWindow::InitChannelDBitComboBox()
{
    ui->DBitComboBox->clear();

    for (const auto &i : SettingConfig::ChannelDBitBaudRate) {
        ui->DBitComboBox->addItem(i.Display);
    }


    ui->DBitComboBox->setCurrentIndex(SettingConfig->GetChannel().DBitBaudRate);
}

void MainWindow::InitChannelResistanceComboBox()
{
    ui->ResistanceComboBox->clear();

    for (const auto &i : SettingConfig::ChannelResistanceEnable) {
        ui->ResistanceComboBox->addItem(i.Display);
    }


    ui->ResistanceComboBox->setCurrentIndex(SettingConfig->GetChannel().Resistance);
}

void MainWindow::InitMessageFrameTypeComboBox()
{
    ui->MessageFrameTypeComboBox->clear();

    for (const auto &i : SettingConfig::MessageFrameType) {
        ui->MessageFrameTypeComboBox->addItem(i.Display);
    }


    ui->MessageFrameTypeComboBox->setCurrentIndex(0);
}

void MainWindow::InitMessageTransmitTypeComboBox()
{
    ui->MessageTransmitComboBox->clear();

    for (const auto &i : SettingConfig::MessageTransmitType) {
        ui->MessageTransmitComboBox->addItem(i.Display);
    }


    ui->MessageTransmitComboBox->setCurrentIndex(0);
}

void MainWindow::InitMessageTable()
{
    auto MessageTable = ui->MessageTable;

    MessageTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    MessageTable->setSelectionMode(QAbstractItemView::SingleSelection);
    MessageTable->setSortingEnabled( false );
    MessageTable->verticalHeader()->hide();
    MessageTable->setWordWrap( false );
    MessageTable->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    MessageTable->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    MessageTable->setShowGrid( false );
    MessageTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    MessageTable->horizontalHeader()->setHighlightSections( false );
    MessageTable->setAlternatingRowColors( true );   // alternative colors
    MessageTable->setFrameShape(QFrame::NoFrame);

    // column width
    MessageTable->setColumnWidth(0, 50);
    MessageTable->setColumnWidth(1, 50);
    MessageTable->setColumnWidth(2, 60);
    MessageTable->setColumnWidth(3, 50);
    MessageTable->setColumnWidth(4, 50);
    MessageTable->setColumnWidth(5, 200);
}

void MainWindow::ResetMessageTable()
{
    while(ui->MessageTable->rowCount()){
        ui->MessageTable->removeRow(0);
    }
}

void MainWindow::InitMessageID()
{
    QRegularExpression regx("[A-Fa-f0-9]{1,4}");
    QValidator* validator = new QRegularExpressionValidator(regx, ui->DataID);
    ui->DataID->setValidator(validator);
}

void MainWindow::InitMessageDLC()
{
    QRegularExpression regx("[0-9]{1,2}");
    QValidator* validator = new QRegularExpressionValidator(regx, ui->DLCEdit);
    ui->DLCEdit->setValidator(validator);
}

void MainWindow::On_OpenDevice()
{
    SDevice ConfigDevice = SettingConfig->GetDevice();
    std::string DeviceDisplayName = (SettingConfig::DeviceName[ConfigDevice.Name].Display).toStdString();
    int DeviceName = SettingConfig::DeviceName[ConfigDevice.Name].Value;
    int DeviceID = ConfigDevice.ID;

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
    cfg.can.mode = SettingConfig::ChannelWorkingMode[ConfigChannel.WorkingMode].Value; //正常模式, 1为只听模式
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

        StartTime = QDateTime::currentDateTime();
        bIsRunThread = true;
    }
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
    std::string DeviceDisplayName = (SettingConfig::DeviceName[ConfigDevice.Name].Display).toStdString();
    qDebug("设备：%s 关闭",(DeviceDisplayName.c_str()));
}

void MainWindow::On_OpenAutoSendConfigWindow()
{

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

bool MainWindow::SetBaudRate()
{
    if (!property) return false;

    SChannel ConfigChannel = SettingConfig->GetChannel();
    char path[50] = { 0 };
    sprintf_s(path, "%d/canfd_abit_baud_rate", ConfigChannel.ID);
    char value[10] = { 0 };
    sprintf_s(value, "%d", SettingConfig::ChannelABitBaudRate[ConfigChannel.ABitBaudRate].Value);
    int ret_a = property->SetValue(path, value);

    sprintf_s(path, "%d/canfd_dbit_baud_rate", ConfigChannel.ID);
    sprintf_s(value, "%d", SettingConfig::ChannelDBitBaudRate[ConfigChannel.DBitBaudRate].Value);
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
    sprintf_s(value, "%d", SettingConfig::ChannelResistanceEnable[ConfigChannel.Resistance].Value);
    return property->SetValue(path, value);
}

void MainWindow::On_SendMessage()
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

void MainWindow::ReceiveData()
{
    ZCAN_Receive_Data can_data[100];
    ZCAN_ReceiveFD_Data canfd_data[100];
    UINT len;

    if (len = ZCAN_GetReceiveNum(chHandle, TYPE_CAN))
    {
        len = ZCAN_Receive(chHandle, can_data, 100, 50);
        AddTableData(can_data, len);
    }
    if (len = ZCAN_GetReceiveNum(chHandle, TYPE_CANFD))
    {
        len = ZCAN_ReceiveFD(chHandle, canfd_data, 100, 50);
        AddTableData(canfd_data, len);
    }
}

void MainWindow::AddTableData(const ZCAN_Receive_Data *data, UINT len)
{
    QString str;
    for (UINT i = 0; i < len; ++i)
    {
        const ZCAN_Receive_Data& can = data[i];
        const canid_t& id = can.frame.can_id;

        TableData InTableData;
        InTableData.ElapsedTime  =   QDateTime::currentDateTime().toMSecsSinceEpoch();
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
    QString str;
    for (UINT i = 0; i < len; ++i)
    {
        const ZCAN_ReceiveFD_Data& canfd = data[i];
        const canid_t& id = canfd.frame.can_id;

        QDateTime time = QDateTime::currentDateTime();

        TableData InTableData;
        InTableData.ElapsedTime  =   QDateTime::currentDateTime().toMSecsSinceEpoch();
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
    QString str;
    for (UINT i = 0; i < len; ++i)
    {
        const ZCAN_Transmit_Data& can = data[i];
        const canid_t& id = can.frame.can_id;

        TableData InTableData;
        InTableData.ElapsedTime  =   QDateTime::currentDateTime().toMSecsSinceEpoch();
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
    QString str;
    for (UINT i = 0; i < len; ++i)
    {
        const ZCAN_TransmitFD_Data& canfd = data[i];
        const canid_t& id = canfd.frame.can_id;

        TableData InTableData;
        InTableData.ElapsedTime  =   QDateTime::currentDateTime().toMSecsSinceEpoch();
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
    int rowIndex = ui->MessageTable->rowCount();//当前表格的行数
    ui->MessageTable->insertRow(rowIndex);//在最后一行的后面插入一行

    QDateTime time = QDateTime::fromMSecsSinceEpoch(InTableData.ElapsedTime);
    qint64 intervalTimeMS = StartTime.msecsTo(time);

    ui->MessageTable->setItem(rowIndex, 0, new QTableWidgetItem(QString::number(intervalTimeMS/1000.0, 'f', 3)));
    ui->MessageTable->setItem(rowIndex, 1, new QTableWidgetItem(QString::number(InTableData.FrameID, 16)));

    switch (InTableData.EventType) {
    case FrameType::CAN:
        ui->MessageTable->setItem(rowIndex, 2, new QTableWidgetItem("CAN"));
        break;
    case FrameType::CANFD:
        ui->MessageTable->setItem(rowIndex, 2, new QTableWidgetItem("CAN FD"));
        break;
    }

    switch (InTableData.DirType) {
    case DirectionType::Receive:
        ui->MessageTable->setItem(rowIndex, 3, new QTableWidgetItem("Rx"));
        break;
    case DirectionType::Transmit:
        ui->MessageTable->setItem(rowIndex, 3, new QTableWidgetItem("Tx"));
        break;
    }

    ui->MessageTable->setItem(rowIndex, 4, new QTableWidgetItem(QString::number(InTableData.DLC, 16)));
    ui->MessageTable->setItem(rowIndex, 5, new QTableWidgetItem(InTableData.Data));

    ui->MessageTable->scrollToBottom();
}

void MainWindow::TransmitCAN()
{
    ZCAN_Transmit_Data can_data;

    canid_t CANID     = GetLineTextValue(ui->DataID).toInt();
    BYTE DLC          = GetLineTextValue(ui->DLCEdit).toInt();
    BYTE TransmitType = ui->MessageTransmitComboBox->currentIndex();

    memset(&can_data, 0, sizeof(can_data));
    can_data.frame.can_id = CANID;         // CAN ID
    can_data.frame.can_dlc = DLC;          // CAN 数据长度
    can_data.transmit_type = TransmitType; //发送模式
    for (int i = 0; i < DLC; ++i)
    {
        can_data.frame.data[i] = GetDataFromEdit(i);
    }
    ZCAN_Transmit_Data* pData = new ZCAN_Transmit_Data[1];
    for (int i=0; i<1; ++i)
    {
        memcpy_s(&pData[i], sizeof(ZCAN_Transmit_Data), &can_data, sizeof(can_data));
    }
    auto result = ZCAN_Transmit(chHandle, pData, 1);
    AddTableData(pData,1);
}

void MainWindow::TransmitCANFD()
{
    ZCAN_TransmitFD_Data canfd_data;

    canid_t CANID = GetLineTextValue(ui->DataID).toInt(nullptr, 16);
    BYTE DLC = GetLineTextValue(ui->DLCEdit).toInt();
    BYTE TransmitType = ui->MessageTransmitComboBox->currentIndex();

    memset(&canfd_data, 0, sizeof(canfd_data));
    canfd_data.frame.can_id = MAKE_CAN_ID(CANID, 0, 0, 0); // CANFD ID
    canfd_data.frame.len = DLC;      // CANFD 数据长度
    canfd_data.transmit_type = TransmitType;
    canfd_data.frame.flags = 1;

    for (int i = 0; i < DLC; ++i)
    {
        canfd_data.frame.data[i] = GetDataFromEdit(i);
    }
//    ZCAN_TransmitFD_Data* pData = new ZCAN_TransmitFD_Data[1];
//    for (int i=0; i<1; ++i)
//    {
//        memcpy_s(&pData[i], sizeof(ZCAN_TransmitFD_Data), &canfd_data, sizeof(canfd_data));
//    }
    auto result = ZCAN_TransmitFD(chHandle, &canfd_data, 1);
    AddTableData(&canfd_data,1);
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
    QVector<DataEdit*>().swap(DataEdits);
    while (QLayoutItem* child = ui->DataContainer->takeAt(0))
    {
        //setParent为NULL，防止删除之后界面不消失
        if(child->widget())
        {
            child->widget()->setParent(NULL);
        }

        delete child;
    }

    int DataLength =  GetLineTextValue(ui->DLCEdit).toInt();
    int RowCount = DataLength / 8;
    if(DataLength % 8 == 0){
        RowCount -= 1;
    }

    //在（0,0）生产 “数据(0x)” 文本
    QLabel* Datalab = new QLabel();
    Datalab->setText(QString("数据(0x)"));
    Datalab->setAlignment(Qt::AlignCenter);
    ui->DataContainer->addWidget(Datalab,0,0);

    for(int i = 0; i < (DataLength > 8 ? 8 : DataLength); i++){
        QLabel* IndexLab = new QLabel();
        IndexLab->setText(QString("%1").arg(i));
        IndexLab->setAlignment(Qt::AlignCenter);
        ui->DataContainer->addWidget(IndexLab,0,i + 1);
    }

    QSpacerItem* Hor = new QSpacerItem(10,10,QSizePolicy::Expanding);
    ui->DataContainer->addItem(Hor, 0, (DataLength > 8 ? 8 : DataLength) + 1);


    int RowRemainDataLength = DataLength;
    DataEdit* Prebt = nullptr;

    for(int i = 0; i < RowCount + 1; i++)
    {
        QLabel* IndexLab = new QLabel();
        IndexLab->setText(QString("%1").arg(i));
        IndexLab->setAlignment(Qt::AlignCenter);
        ui->DataContainer->addWidget(IndexLab, i + 1, 0);

        for(int j = 1; j < (RowRemainDataLength > 8 ? 8 : RowRemainDataLength) + 1; j++){
            DataEdit* bt = new DataEdit();

            if(Prebt){
                Prebt->SetNextEdit(bt);
            }
            Prebt = bt;

            bt->setPlaceholderText("00");
            bt->setAlignment(Qt::AlignCenter);
            ui->DataContainer->addWidget(bt, i + 1, j);

            DataEdits.append(bt);
        }
        RowRemainDataLength -= 8;
        if(RowRemainDataLength < 0) RowRemainDataLength = 0;
    }
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
        return DataEdits[Index]->text().toInt(nullptr,16);
    }
}

void MainWindow::GetViewCanFrame(ZCAN_Transmit_Data &can_data)
{
    canid_t CANID     = GetLineTextValue(ui->DataID).toInt();
    BYTE DLC          = GetLineTextValue(ui->DLCEdit).toInt();
    BYTE TransmitType = ui->MessageTransmitComboBox->currentIndex();

    memset(&can_data, 0, sizeof(can_data));
    can_data.frame.can_id   =  MAKE_CAN_ID(CANID, 0, 0, 0);         // CAN ID
    can_data.frame.can_dlc  =  DLC;          // CAN 数据长度
    can_data.transmit_type  =  TransmitType; //发送模式

    for (int i = 0; i < DLC; ++i)
    {
        can_data.frame.data[i] = GetDataFromEdit(i);
    }
}

void MainWindow::GetViewCanFrame(ZCAN_TransmitFD_Data& canfd_data)
{
    canid_t CANID = GetLineTextValue(ui->DataID).toInt(nullptr, 16);
    BYTE DLC = GetLineTextValue(ui->DLCEdit).toInt();
    BYTE TransmitType = ui->MessageTransmitComboBox->currentIndex();

    memset(&canfd_data, 0, sizeof(canfd_data));
    canfd_data.frame.can_id   =  MAKE_CAN_ID(CANID, 0, 0, 0); // CANFD ID
    canfd_data.frame.len      =  DLC;                            // CANFD 数据长度
    canfd_data.transmit_type  =  TransmitType;
    canfd_data.frame.flags    =  1;

    for (int i = 0; i < DLC; ++i)
    {
        canfd_data.frame.data[i] = GetDataFromEdit(i);
    }
}
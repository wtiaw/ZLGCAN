#include "QDeviceSettingConfig.h"
#include "QFileInfo"
#include <iostream>

QVector<DisplayAndValue<int>> QDeviceSettingConfig::DeviceName = {
        DisplayAndValue("USBCANFD_200U", ZCAN_USBCANFD_200U)
    };

QVector<DisplayAndValue<int>> QDeviceSettingConfig::ChannelWorkingMode = {
        DisplayAndValue("正常模式", 0),
        DisplayAndValue("只听模式", 1)
    };

QVector<DisplayAndValue<int>> QDeviceSettingConfig::ChannelABitBaudRate = {
    DisplayAndValue("50kps",  50000),
    DisplayAndValue("100kps", 100000),
    DisplayAndValue("125kps", 125000),
    DisplayAndValue("250kps", 250000),
    DisplayAndValue("500kps", 500000),
    DisplayAndValue("800kps", 800000),
    DisplayAndValue("1Mps",   1000000)
};

QVector<DisplayAndValue<int>> QDeviceSettingConfig::ChannelDBitBaudRate = {
    DisplayAndValue("100kps", 100000),
    DisplayAndValue("125kps", 125000),
    DisplayAndValue("250kps", 250000),
    DisplayAndValue("500kps", 500000),
    DisplayAndValue("800kps", 800000),
    DisplayAndValue("1Mps",   1000000),
    DisplayAndValue("2Mps",   2000000),
    DisplayAndValue("4Mps",   4000000),
    DisplayAndValue("5Mps",   5000000)
};

QVector<DisplayAndValue<int>> QDeviceSettingConfig::ChannelResistanceEnable = {
    DisplayAndValue("关闭", 0),
    DisplayAndValue("开启", 1)
};

QVector<DisplayAndValue<int>> QDeviceSettingConfig::MessageFrameType = {
    DisplayAndValue("CAN", 0),
    DisplayAndValue("CANFD", 1)
};

QVector<DisplayAndValue<int>> QDeviceSettingConfig::MessageTransmitType = {
    DisplayAndValue("正常发送", 0),
    DisplayAndValue("单次发送", 1),
    DisplayAndValue("自发自收", 2)
};

QDeviceSettingConfig::QDeviceSettingConfig(QObject *parent)
    : QSettingConfigBase{parent}
{
    //路径
    ConfigFilePath = QDir::currentPath()+QString("/CanSetting.config");
}

void QDeviceSettingConfig::ReadConfig()
{
    QSettingConfigBase::ReadConfig();

    if(!psetting)
        psetting = new QSettings(ConfigFilePath,QSettings::IniFormat);


    Device.Name = psetting->value(DeviceNamePath).toInt();
    Device.ID = psetting->value(DeviceIDPath).toUInt();

    Channel.ID = psetting->value(ChannelIDPath).toUInt();
    Channel.WorkingMode = psetting->value(ChannelWorkingModePath).toInt();
    Channel.ABitBaudRate = psetting->value(ChannelABitBaudRatePath).toInt();
    Channel.DBitBaudRate = psetting->value(ChannelDBitBaudRatePath).toInt();
    Channel.Resistance = psetting->value(ChannelResistancePath).toInt();
}

void QDeviceSettingConfig::InitConfig()
{
    if(!psetting)
        psetting = new QSettings(ConfigFilePath,QSettings::IniFormat);

    SaveConfig(DeviceNamePath, 0);
    SaveConfig(DeviceIDPath,   0);

    SaveConfig(ChannelIDPath, 0);
    SaveConfig(ChannelWorkingModePath, 0);
    SaveConfig(ChannelABitBaudRatePath, 4);
    SaveConfig(ChannelDBitBaudRatePath, 6);
    SaveConfig(ChannelResistancePath, 1);
}

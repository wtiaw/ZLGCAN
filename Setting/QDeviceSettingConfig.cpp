#include "QDeviceSettingConfig.h"
#include "QFileInfo"
#include <QJsonObject>
#include <iostream>


QVector<DisplayAndValue<int>> QDeviceSettingConfig::DeviceName = {
    DisplayAndValue("USBCANFD_200U", ZCAN_USBCANFD_200U)
};

QVector<DisplayAndValue<int>> QDeviceSettingConfig::ChannelWorkingMode = {
    DisplayAndValue("正常模式", 0),
    DisplayAndValue("只听模式", 1)
};

QVector<DisplayAndValue<int>> QDeviceSettingConfig::ChannelABitBaudRate = {
    DisplayAndValue("50kps", 50000),
    DisplayAndValue("100kps", 100000),
    DisplayAndValue("125kps", 125000),
    DisplayAndValue("250kps", 250000),
    DisplayAndValue("500kps", 500000),
    DisplayAndValue("800kps", 800000),
    DisplayAndValue("1Mps", 1000000)
};

QVector<DisplayAndValue<int>> QDeviceSettingConfig::ChannelDBitBaudRate = {
    DisplayAndValue("100kps", 100000),
    DisplayAndValue("125kps", 125000),
    DisplayAndValue("250kps", 250000),
    DisplayAndValue("500kps", 500000),
    DisplayAndValue("800kps", 800000),
    DisplayAndValue("1Mps", 1000000),
    DisplayAndValue("2Mps", 2000000),
    DisplayAndValue("4Mps", 4000000),
    DisplayAndValue("5Mps", 5000000)
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

QDeviceSettingConfig::QDeviceSettingConfig(QObject* parent)
    : QSettingConfigBase{parent}
{
    //路径
    ConfigFilePath = "/DeviceSetting.json";
}

void QDeviceSettingConfig::ReadConfig(QJsonDocument& doc, QJsonObject& RootObject)
{
    QSettingConfigBase::ReadConfig(doc, RootObject);

    QFile file(ConfigDirPath + ConfigFilePath);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "can't open error!";
        return;
    }

    // 读取文件的全部内容
    QTextStream stream(&file);
    QString str = stream.readAll();

    file.close();

    // QJsonParseError类用于在JSON解析期间报告错误。
    QJsonParseError jsonError;
    // 将json解析为UTF-8编码的json文档，并从中创建一个QJsonDocument。
    // 如果解析成功，返回QJsonDocument对象，否则返回null
    doc = QJsonDocument::fromJson(str.toUtf8(), &jsonError);
    // 判断是否解析失败
    if (jsonError.error != QJsonParseError::NoError && !doc.isNull())
    {
        qDebug() << "Json格式错误！" << jsonError.error;
        return;
    }

    RootObject = doc.object();

    QJsonValue interestValue = RootObject.value("Channel");
    if (interestValue.type() == QJsonValue::Object)
    {
        const QJsonObject ChannelObj = interestValue.toObject();

        const QJsonValue ChannelABitBaudRateValue = ChannelObj.value("ChannelABitBaudRate");
        Channel.ABitBaudRate = ChannelABitBaudRateValue.toInt();
        qDebug() << "ChannelABitBaudRate = " << ChannelABitBaudRateValue.toInt();

        const QJsonValue ChannelDBitBaudRate = ChannelObj.value("ChannelDBitBaudRate");
        Channel.DBitBaudRate = ChannelDBitBaudRate.toInt();
        qDebug() << "ChannelDBitBaudRate = " << ChannelDBitBaudRate.toInt();

        const QJsonValue ChannelID = ChannelObj.value("ChannelID");
        Channel.ID = ChannelID.toInt();
        qDebug() << "ChannelID = " << ChannelID.toInt();

        const QJsonValue ChannelResistance = ChannelObj.value("ChannelResistance");
        Channel.Resistance = ChannelResistance.toInt();
        qDebug() << "ChannelResistance = " << ChannelResistance.toInt();

        const QJsonValue ChannelWorkingMode = ChannelObj.value("ChannelWorkingMode");
        Channel.WorkingMode = ChannelWorkingMode.toInt();
        qDebug() << "ChannelWorkingMode = " << ChannelWorkingMode.toInt();
    }

    interestValue = RootObject.value("Device");
    if (interestValue.type() == QJsonValue::Object)
    {
        const QJsonObject ChannelObj = interestValue.toObject();

        const QJsonValue DeviceID = ChannelObj.value("DeviceID");
        Device.ID = DeviceID.toInt();
        qDebug() << "DeviceID = " << DeviceID.toInt();

        const QJsonValue DeviceName = ChannelObj.value("DeviceName");
        Device.Name = DeviceName.toInt();
        qDebug() << "DeviceName = " << DeviceName.toInt();
    }
}

void QDeviceSettingConfig::InitConfig()
{
    QJsonObject DeviceObj;
    DeviceObj.insert("DeviceName", 0);
    DeviceObj.insert("DeviceID", 0);

    QJsonObject ChannelObj;
    ChannelObj.insert("ChannelID", 0);
    ChannelObj.insert("ChannelWorkingMode", 0);
    ChannelObj.insert("ChannelABitBaudRate", 4);
    ChannelObj.insert("ChannelDBitBaudRate", 6);
    ChannelObj.insert("ChannelResistance", 1);

    QJsonObject rootObject;
    rootObject.insert("Channel", ChannelObj);
    rootObject.insert("Device", DeviceObj);


    // 将json对象里的数据转换为字符串
    QJsonDocument doc;
    // 将object设置为本文档的主要对象
    doc.setObject(rootObject);

    QFile file(ConfigDirPath + ConfigFilePath);
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);

    QTextStream stream(&file);
    stream << doc.toJson();
    file.close();
}

void QDeviceSettingConfig::SaveConfig(QString ObjectName, QString Key, int Value)
{
    Save(ConfigDirPath + ConfigFilePath, ObjectName, Key, Value);
}

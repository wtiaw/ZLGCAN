#ifndef SETTINGCONFIG_H
#define SETTINGCONFIG_H

#include <QObject>
#include "zlgcan.h"
#include "QSettings"

#define DeviceNamePath               "/Device/Name"
#define DeviceIDPath                 "/Device/ID"
#define ChannelIDPath                "/Channel/ID"
#define ChannelWorkingModePath       "/Channel/WorkingMode"
#define ChannelABitBaudRatePath      "/Channel/ABitBaudRate"
#define ChannelDBitBaudRatePath      "/Channel/DBitBaudRate"
#define ChannelResistancePath        "/Channel/Resistance"

template<class ValueClass>
struct DisplayAndValue
{
    DisplayAndValue() {}
    DisplayAndValue(QString Display,ValueClass Value) {
        this->Display = Display;
        this->Value = Value;
    }

    QString Display;

    ValueClass Value;
};

struct SDevice
{
    int Name;
    int ID;
};

struct SChannel
{
    int ID;
    int WorkingMode;
    int ABitBaudRate;
    int DBitBaudRate;
    int Resistance;
};



class SettingConfig : public QObject
{
    Q_OBJECT
public:
    explicit SettingConfig(QObject *parent = nullptr);

    static QVector<DisplayAndValue<int>> DeviceName;

    static QVector<DisplayAndValue<int>> ChannelWorkingMode;
    static QVector<DisplayAndValue<int>> ChannelABitBaudRate;
    static QVector<DisplayAndValue<int>> ChannelDBitBaudRate;
    static QVector<DisplayAndValue<int>> ChannelResistanceEnable;

    static QVector<DisplayAndValue<int>> MessageTransmitType;
    static QVector<DisplayAndValue<int>> MessageFrameType;

    SDevice& GetDevice(){ return Device; }
    SChannel& GetChannel(){ return Channel; }


    void ReadConfig();
    void InitConfig();

    void SaveConfig(std::string key, int Value);

signals:
private:
    QString qstrConfigPath;
    QSettings *psetting = nullptr;

    SDevice Device;
    SChannel Channel;
};

#endif // SETTINGCONFIG_H

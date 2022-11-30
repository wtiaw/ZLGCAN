#include "QAutoMessageConfig.h"
#include "qjsonobject.h"

QAutoMessageConfig::QAutoMessageConfig(QObject *parent)
    : QSettingConfigBase{parent}
{
    //路径
    ConfigFilePath = "AutoMessageSetting";
}

void QAutoMessageConfig::ReadConfig()
{
    return;
}

void QAutoMessageConfig::InitConfig()
{

}

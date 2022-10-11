#include "QAutoMessageConfig.h"

QAutoMessageConfig::QAutoMessageConfig(QObject *parent)
    : QSettingConfigBase{parent}
{
    //路径
    ConfigFilePath = "/AutoMessageSetting.config";
}

void QAutoMessageConfig::ReadConfig()
{

}

void QAutoMessageConfig::InitConfig()
{

}

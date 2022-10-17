#include "QAutoMessageConfig.h"
#include "qjsonobject.h"

QAutoMessageConfig::QAutoMessageConfig(QObject *parent)
    : QSettingConfigBase{parent}
{
    //路径
    ConfigFilePath = "/AutoMessageSetting.config";
}

void QAutoMessageConfig::ReadConfig(QJsonDocument& doc, QJsonObject& RootObject)
{
    return;
}

void QAutoMessageConfig::InitConfig()
{

}

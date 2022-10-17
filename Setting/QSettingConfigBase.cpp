#include "QSettingConfigBase.h"

QSettingConfigBase::QSettingConfigBase(QObject *parent)
    : QObject{parent}
{
    ConfigDirPath = QDir::currentPath() + "/Config";
}

void QSettingConfigBase::ReadConfig(QJsonDocument& doc, QJsonObject& RootObject)
{
    QDir dir(ConfigDirPath);
    if(!dir.exists()){
        bool ismkdir = dir.mkdir(ConfigDirPath);
        if(!ismkdir)
            qDebug() << "Create path fail" << Qt::endl;
        else
            qDebug() << "Create fullpath success" << Qt::endl;
    }

    QFileInfo fi(ConfigDirPath + ConfigFilePath);
    if(!fi.isFile()){
        InitConfig();
    }
}

void QSettingConfigBase::InitConfig()
{

}

void QSettingConfigBase::SaveConfig(QString ObjectName, QString key, int Value)
{

}



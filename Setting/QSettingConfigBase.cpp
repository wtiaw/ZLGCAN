#include "QSettingConfigBase.h"

QSettingConfigBase::QSettingConfigBase(QObject* parent)
    : QObject{parent}
{
    ConfigDirPath = QDir::currentPath() + "/Config";
}

void QSettingConfigBase::ReadConfig(QJsonDocument& doc, QJsonObject& RootObject)
{
    if (const QDir dir(ConfigDirPath); !dir.exists())
    {
        if (const bool ismkdir = dir.mkdir(ConfigDirPath); !ismkdir)
            qDebug() << "Create path fail" << Qt::endl;
        else
            qDebug() << "Create fullpath success" << Qt::endl;
    }

    if (const QFileInfo fi(ConfigDirPath + ConfigFilePath); !fi.isFile())
    {
        InitConfig();
    }
}

void QSettingConfigBase::InitConfig()
{
}

void QSettingConfigBase::SaveConfig(QString ObjectName, QString key, int Value)
{
}

#include "QSettingConfigBase.h"

#include <utility>

QSettingConfigBase::QSettingConfigBase(QObject* parent)
    : QObject{parent}
{
    ConfigDirPath = QDir::currentPath() + "/Config";
}

void QSettingConfigBase::SetConfigFilePath(const QString& InConfigFilePath)
{
    this->ConfigFilePath = InConfigFilePath;
    this->FullFilePath = QString("%1/%2.json").arg(ConfigDirPath, ConfigFilePath);
}

void QSettingConfigBase::ReadConfig()
{
    if (const QDir dir(ConfigDirPath); !dir.exists())
    {
        if (const bool ismkdir = dir.mkdir(ConfigDirPath); !ismkdir)
            qDebug() << "Create path fail" << Qt::endl;
        else
            qDebug() << "Create full path success" << Qt::endl;
    }
    
    if (const QFileInfo fi(FullFilePath); !fi.isFile())
    {
        InitConfig();
    }
}

void QSettingConfigBase::InitConfig()
{
    QFile file(FullFilePath);
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);

    file.close();

    qDebug() << "Create File" << FullFilePath;
}

void QSettingConfigBase::SaveConfig(const QString& ObjectName, const QString& key, int Value)
{
    Save(FullFilePath, ObjectName, key, Value);
}

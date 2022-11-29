#include "QSettingConfigBase.h"

#include <utility>

QSettingConfigBase::QSettingConfigBase(QObject* parent)
    : QObject{parent}
{
    ConfigDirPath = QDir::currentPath() + "/Config";
}

void QSettingConfigBase::ReadConfig()
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
    QFile file(ConfigDirPath + ConfigFilePath);
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);

    file.close();

    qDebug() << "Create File" << ConfigDirPath + ConfigFilePath;
}

void QSettingConfigBase::SaveConfig(const QString& ObjectName, const QString& key, int Value)
{
    Save(ConfigDirPath + ConfigFilePath, ObjectName, key, Value);
}

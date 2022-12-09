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

bool QSettingConfigBase::IsFileValid(QFile& file) const
{
    qDebug() << "ReadConfig" << FullFilePath;
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "can't open error!";
        return false;
    }

    return true;
}

QString QSettingConfigBase::ReadFileData(QFile& file) const
{
    // 读取文件的全部内容
    QTextStream stream(&file);
    const QString str = stream.readAll();

    file.close();
    return str;
}

bool QSettingConfigBase::ReadJsonFile(const QString& str, QJsonDocument& doc) const
{
    // QJsonParseError类用于在JSON解析期间报告错误。
    QJsonParseError jsonError;
    // 将json解析为UTF-8编码的json文档，并从中创建一个QJsonDocument。
    // 如果解析成功，返回QJsonDocument对象，否则返回null
    doc = QJsonDocument::fromJson(str.toUtf8(), &jsonError);
    // 判断是否解析失败
    if (jsonError.error != QJsonParseError::NoError && !doc.isNull())
    {
        qDebug() << "Json格式错误！" << jsonError.error;
        return false;
    }

    return true;
}

#ifndef QSETTINGCONFIGBASE_H
#define QSETTINGCONFIGBASE_H

#include <QObject>
#include "QSettings"
#include "QDir"
#include <qjsonobject>
#include <QJsonDocument>

class QSettingConfigBase : public QObject
{
    Q_OBJECT
public:
    explicit QSettingConfigBase(QObject* parent = nullptr);

    [[nodiscard]] QString GetConfigFilePath() const { return ConfigFilePath; }
    void SetConfigFilePath(const QString& InConfigFilePath);

    virtual void ReadConfig();
    virtual void InitConfig();
    virtual void SaveConfig(const QString& ObjectName, const QString& key, int Value);

    template <typename ValueType>
    void Save(const QString& FileName, const QString& ObjectName, const QString& key, ValueType Value);

protected:
    bool IsFileValid(QFile& file) const;
    QString ReadFileData(QFile& file) const;
    bool ReadJsonFile(const QString& str, QJsonDocument& doc) const;
    
signals:
protected:
    QString ConfigDirPath;
    QString ConfigFilePath;
    QString FullFilePath;
};

template <typename ValueType>
void QSettingConfigBase::Save(const QString& FileName, const QString& ObjectName, const QString& key, ValueType Value)
{
    QJsonObject RootObject;
    QJsonDocument doc;

    ReadConfig();
    if (const QJsonValue interestValue = RootObject.value(ObjectName); interestValue.type() == QJsonValue::Object)
    {
        QJsonObject interestObject = interestValue.toObject();

        interestObject[key] = Value;

        RootObject[ObjectName] = interestObject;
    }

    // 将object设置为本文档的主要对象
    doc.setObject(RootObject);

    // 重写打开文件，覆盖原有文件，达到删除文件全部内容的效果
    QFile writeFile(FileName);
    if (!writeFile.open(QFile::WriteOnly | QFile::Truncate))
    {
        qDebug() << "can't open error!";
        return;
    }

    // 将修改后的内容写入文件
    QTextStream writeStream(&writeFile);
    writeStream << doc.toJson(); // 写入文件
    writeFile.close(); // 关闭文件

    ReadConfig();
}

#endif // QSETTINGCONFIGBASE_H

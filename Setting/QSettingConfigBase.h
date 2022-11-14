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

    virtual void ReadConfig(QJsonDocument& doc, QJsonObject& RootObject);
    virtual void InitConfig();
    virtual void SaveConfig(QString ObjectName, QString key, int Value);

    template <typename ValueType>
    void Save(QString FileName, QString ObjectName, QString key, ValueType Value);
signals:
protected:
    QString ConfigDirPath;
    QString ConfigFilePath;

    QSettings* psetting = nullptr;
};

template <typename ValueType>
void QSettingConfigBase::Save(QString FileName, QString ObjectName, QString key, ValueType Value)
{
    QJsonObject RootObject;
    QJsonDocument doc;

    ReadConfig(doc, RootObject);
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

    ReadConfig(doc, RootObject);
}

#endif // QSETTINGCONFIGBASE_H

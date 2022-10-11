#ifndef QSETTINGCONFIGBASE_H
#define QSETTINGCONFIGBASE_H

#include <QObject>
#include "QSettings"
#include "QDir"

class QSettingConfigBase : public QObject
{
    Q_OBJECT
public:
    explicit QSettingConfigBase(QObject *parent = nullptr);

    virtual void ReadConfig();
    virtual void InitConfig();

    void SaveConfig(std::string key, int Value);
signals:

protected:
    QString ConfigDirPath;
    QString ConfigFilePath;

    QSettings *psetting = nullptr;
};

#endif // QSETTINGCONFIGBASE_H

#ifndef QAUTOMESSAGECONFIG_H
#define QAUTOMESSAGECONFIG_H

#include "QSettingConfigBase.h"

class QAutoMessageConfig : public QSettingConfigBase
{
    Q_OBJECT
public:
    explicit QAutoMessageConfig(QObject *parent = nullptr);

    virtual void ReadConfig(QJsonDocument& doc, QJsonObject& RootObject) override;
    virtual void InitConfig() override;
};

#endif // QAUTOMESSAGECONFIG_H

#ifndef QAUTOMESSAGECONFIG_H
#define QAUTOMESSAGECONFIG_H

#include "QSettingConfigBase.h"

class QAutoMessageConfig : public QSettingConfigBase
{
    Q_OBJECT
public:
    explicit QAutoMessageConfig(QObject *parent = nullptr);
    
    void ReadConfig() override;
    void InitConfig() override;
};

#endif // QAUTOMESSAGECONFIG_H

#ifndef QSYSTEMVARIABLES_H
#define QSYSTEMVARIABLES_H

#include "QSettingConfigBase.h"
#include "Data/VariableStruct.h"

class QSystemVariables : public QSettingConfigBase
{
public:
    explicit QSystemVariables(QObject* parent = nullptr);

    void ReadConfig() override;
    void InitConfig() override;

    void SaveConfig(const QJsonDocument& doc) const;

public:
    static QMultiMap<QString, VariableNamespace> Variables;
};

#endif

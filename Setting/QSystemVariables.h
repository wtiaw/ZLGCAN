#ifndef QSYSTEMVARIABLES_H
#define QSYSTEMVARIABLES_H

#include "QSettingConfigBase.h"
#include "Data/CustomEnum.h"
#include "Data/VariableStruct.h"

class QSystemVariables : public QSettingConfigBase
{
public:
    explicit QSystemVariables(QObject* parent = nullptr);

    void ReadConfig() override;
    void InitConfig() override;

    void SaveConfig(const QJsonDocument& doc) const;

    [[nodiscard]] CustomEnum::EFormType GetCurrentType() const;

    void SetCurrentType(const CustomEnum::EFormType CurrentType);

    static QMultiMap<QString, VariableNamespace> Variables;

private:
    CustomEnum::EFormType CurrentType = CustomEnum::EFormType::None;
};

#endif

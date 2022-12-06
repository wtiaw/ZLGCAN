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

private:
    template <typename T>
    void SetVariable(VariableEntity<T>* InVariableBase, const QJsonObject& InJsonValue);

    template <typename T>
    T GetJsonValue(const QJsonValue& InJsonValue);

    template <>
    int GetJsonValue(const QJsonValue& InJsonValue);

    template <>
    uint GetJsonValue(const QJsonValue& InJsonValue);

    template <>
    double GetJsonValue(const QJsonValue& InJsonValue);

    template <>
    QString GetJsonValue(const QJsonValue& InJsonValue);
};

QList<ValueTable> GetVariablesByNamespaceAndName(const QString& NamespaceAndName);

int GetTableValueByIndex(const QList<ValueTable>&, int Index);

template <typename T>
void QSystemVariables::SetVariable(VariableEntity<T>* InVariableBase, const QJsonObject& InJsonValue)
{
    QJsonValue StartValueJV = InJsonValue.value("startValue");
    QJsonValue MaxValueJV = InJsonValue.value("maxValue");
    QJsonValue MinValueJV = InJsonValue.value("minValue");
    QJsonValue CommentJV = InJsonValue.value("comment");
    QJsonValue ValueTableJV = InJsonValue.value("valuetable");


    if (!StartValueJV.isUndefined())
    {
        InVariableBase->bHasInitialValue = true;

        InVariableBase->InitialValue = GetJsonValue<T>(StartValueJV);
    }

    if (!MaxValueJV.isUndefined())
    {
        InVariableBase->bHasMax = true;

        InVariableBase->Max = GetJsonValue<T>(MaxValueJV);
    }

    if (!MinValueJV.isUndefined())
    {
        InVariableBase->bHasMin = true;

        InVariableBase->Min = GetJsonValue<T>(MinValueJV);
    }
}

template <typename T>
T QSystemVariables::GetJsonValue(const QJsonValue& InJsonValue)
{
    return InJsonValue.toInt();
}

template <>
inline int QSystemVariables::GetJsonValue(const QJsonValue& InJsonValue)
{
    const QString Value = InJsonValue.toString();
    return Value.toInt();
}

template <>
inline uint QSystemVariables::GetJsonValue(const QJsonValue& InJsonValue)
{
    const QString Value = InJsonValue.toString();
    return Value.toUInt();
}

template <>
inline double QSystemVariables::GetJsonValue(const QJsonValue& InJsonValue)
{
    const QString Value = InJsonValue.toString();
    return Value.toDouble();
}

template <>
inline QString QSystemVariables::GetJsonValue(const QJsonValue& InJsonValue)
{
    return InJsonValue.toString();
}

#endif

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

    void SaveConfig(const QJsonDocument& InDoc) const;

    [[nodiscard]] CustomEnum::EFormType GetCurrentType() const;

    void SetCurrentType(const CustomEnum::EFormType CurrentType);

public:
    //静态
    static bool IsValidNamespaceAndName(const QString& Namespace, const QString& Name);
    static QList<ValueTable> GetVariablesByNamespaceAndName(const QString& Namespace, const QString& Name);
    static QVariableBase* GetVariableBaseByNamespaceAndName(const QString& Namespace, const QString& Name);

private:
    CustomEnum::EFormType CurrentType = CustomEnum::EFormType::None;

public:
    //静态
    static QMultiMap<QString, VariableNamespacePair> Variables;
    static QList<VariableSavedStruct> NeedSaveVariables;

    static QJsonDocument doc;
    
private:
    template <typename T>
    void SetVariable(QVariableBase* InVariableBase, const QJsonObject& InJsonValue);
};


int GetTableValueByIndex(const QList<ValueTable>&, int Index);

template <typename T>
void QSystemVariables::SetVariable(QVariableBase* InVariableBase, const QJsonObject& InJsonValue)
{
    QJsonValue StartValueJV = InJsonValue.value("startValue");
    QJsonValue MaxValueJV = InJsonValue.value("maxValue");
    QJsonValue MinValueJV = InJsonValue.value("minValue");
    QJsonValue CommentJV = InJsonValue.value("comment");
    QJsonValue ValueTableJV = InJsonValue.value("valuetable");


    if (!StartValueJV.isUndefined())
    {
        InVariableBase->bHasInitialValue = true;

        InVariableBase->InitialValue = StartValueJV.toString();
    }

    if (!MaxValueJV.isUndefined())
    {
        InVariableBase->bHasMax = true;

        InVariableBase->MaxValue = MaxValueJV.toString();
    }

    if (!MinValueJV.isUndefined())
    {
        InVariableBase->bHasMin = true;

        InVariableBase->MinValue = MinValueJV.toString();
    }
}

#endif

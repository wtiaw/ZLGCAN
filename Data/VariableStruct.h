#ifndef VARIABLESTRUCT_H
#define VARIABLESTRUCT_H
#include <QString>
#include <QObject>
#include <qmetaobject.h>

#define GET_VARIABLE_NAME(Namespace,Name) QString("%1::%2").arg(Namespace, Name)


enum ValueType
{
    Null,
    Int,
    UInt,
    Double,
    String,
};

struct ValueTable
{
    QString DisplayName;
    int Value;
};

class QVariableBase : public QObject
{
    Q_OBJECT
    // friend class VariableEntity;
public:
    virtual ~QVariableBase() = default;
    ValueType DataType{};

    bool bShouldSave{};
    bool bHasComment{};
    bool bHasInitialValue{};
    bool bHasMin{};
    bool bHasMax{};

    QString InitialValue{};
    QString MinValue{};
    QString MaxValue{};

    QString Comment = "-";

    QList<ValueTable> ValueTables;

private:
    QString CurrentValue{};

public:
    QString GetCurrentValue() const
    {
        return CurrentValue;
    }

    template <typename T>
    void SetCurrentValue(const T& InCurrentValue)
    {
        CurrentValue = QString::number(InCurrentValue);
    }

    template <>
    void SetCurrentValue(const QString& InCurrentValue)
    {
        if (InCurrentValue != CurrentValue)
        {
            CurrentValue = InCurrentValue;
        }
    }
};

struct VariableNamespacePair
{
    QMap<QString, QVariableBase*> Variables{};
};

struct VariableSavedStruct
{
    QString Namespace;
    QString Name;

    QVariableBase* QVariableBase;
    QString PreValue;

    int count{0};
};

#endif

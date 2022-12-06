#ifndef VARIABLESTRUCT_H
#define VARIABLESTRUCT_H
#include <QString>

enum EDataType
{
    Null,
    Int32,
    UInt32,
    Double,
    String,
    intarray,
};

struct ValueTable
{
    QString DisplayName;
    int Value;
};

class VariableBase
{
public:
    virtual ~VariableBase() = default;
    EDataType DataType{};

    bool bShouldSave{};
    bool bHasComment{};
    bool bHasInitialValue{};
    bool bHasMin{};
    bool bHasMax{};

    QString Comment = "-";
    // T InitialValue;
    // T Min;
    // T Max;
    // T CurrentValue;

    QList<ValueTable> ValueTables;

    virtual void NullFuc(){}
};

template<typename T>
class VariableEntity : public VariableBase
{
public:
    T InitialValue{};
    T Min{};
    T Max{};
    T CurrentValue{};
};
// class Int32Value : public VariableBase
// {
//     int InitialValue = 0;
//     int Min = 0;
//     int Max = 0;
//     int CurrentValue = 0;
// };

// class UInt32Value : public VariableBase
// {
//     uint InitialValue = 0;
//     uint Min = 0;
//     uint Max = 0;
//     uint CurrentValue = 0;
// };
//
// class DoubleValue : public VariableBase
// {
//     double InitialValue = 0;
//     double Min = 0;
//     double Max = 0;
//     double CurrentValue = 0;
// };
//
// class StringValue : public VariableBase
// {
//     QString InitialValue;
//     QString Min;
//     QString Max;
//     QString CurrentValue;
// };

struct VariableNamespace
{
    QMap<QString, VariableBase*> Variables{};
};

#endif

#ifndef VARIABLESTRUCT_H
#define VARIABLESTRUCT_H
#include <QString>

enum EDataType
{
    Int32,
    UInt32,
    Double,
    String,
};

struct ValueTable
{
    QString DisplayName;
    int Value;
};

struct VariableStruct
{
    EDataType DataType;
    
    bool bHasComment{};
    bool bHasInitialValue{};
    bool bHasMin{};
    bool bHasMax{};
    
    QString Comment = "-";
    QString InitialValue = "-";
    QString Min = "-";
    QString Max = "-";
    QList<ValueTable> ValueTables;
};

struct VariableNamespace
{
    QMap<QString, VariableStruct> Variables;
};

#endif

#include "QSystemVariables.h"

#include <qjsonarray.h>

QMultiMap<QString, VariableNamespacePair> QSystemVariables::Variables;
QList<VariableSavedStruct> QSystemVariables::NeedSaveVariables;

QSystemVariables::QSystemVariables([[maybe_unused]] QObject* parent)
{
    ConfigDirPath += "/SystemVariables";
    SetConfigFilePath("SystemVariables");
}

void QSystemVariables::ReadConfig()
{
    QSettingConfigBase::ReadConfig();

    QFile file(FullFilePath);
    if (!IsFileValid(file)) return;

    // 读取文件的全部内容
    const QString str = ReadFileData(file);

    // 读取Json
    QJsonDocument doc;
    if (!ReadJsonFile(str, doc)) return;

    QMultiMap<QString, VariableNamespacePair> temp;
    Variables.swap(temp);

    const QJsonObject RootObject = doc.object();
    QJsonValue interestValue = RootObject.value("namespace");
    if (interestValue.isUndefined())
    {
        qDebug() << "No Config!";
        return;
    }


    const QJsonArray NameSpaceArr = interestValue.toArray();

    for (int i = 0; i < NameSpaceArr.count(); i++)
    {
        QJsonValue NamespaceValueChild = NameSpaceArr.at(i);
        VariableNamespacePair Variable;

        if (NamespaceValueChild.type() == QJsonValue::Object)
        {
            QJsonObject NamespaceObj = NamespaceValueChild.toObject();

            //命名空间
            QString NamespaceName = NamespaceObj.value("name").toString();

            //变量
            QJsonArray VariableArr = NamespaceObj.value("variable").toArray();
            for (auto VariableRef : VariableArr)
            {
                QJsonObject VariableObj = VariableRef.toObject();

                QString VariableName = VariableObj.value("name").toString();
                QString BitCount = VariableObj.value("bitcount").toString();
                QString IsSigned = VariableObj.value("isSigned").toString();
                QString Type = VariableObj.value("type").toString();
                bool bShouldSave = VariableObj.value("shouldSave").toBool();
                QString Comment;

                QJsonValue CommentJV = VariableObj.value("comment");
                QJsonValue ValueTableJV = VariableObj.value("valuetable");

                QVariableBase* VariableBase = new QVariableBase;
                if (Type == "int")
                {
                    if (IsSigned == "true")
                    {
                        SetVariable<uint>(VariableBase, VariableObj);
                    }
                    else
                    {
                        SetVariable<int>(VariableBase, VariableObj);
                    }
                }
                else if (Type == "float")
                {
                    SetVariable<double>(VariableBase, VariableObj);
                }
                else
                {
                    SetVariable<QString>(VariableBase, VariableObj);
                }

                VariableBase->bShouldSave = bShouldSave;

                if (!CommentJV.isUndefined())
                {
                    Comment = CommentJV.toString();
                    VariableBase->bHasComment = true;

                    VariableBase->Comment = Comment;
                }

                if (!ValueTableJV.isUndefined())
                {
                    QJsonArray ValueTablesArray = ValueTableJV.toArray();

                    for (auto ValueTableRef : ValueTablesArray)
                    {
                        QJsonObject ValueTableObj = ValueTableRef.toObject();

                        QString ValueTableName = ValueTableObj.value("displayString").toString();
                        QString Value = ValueTableObj.value("value").toString();
                    }
                }

                if (Type == "int")
                {
                    if (IsSigned == "true")
                    {
                        VariableBase->DataType = ValueType::UInt;
                    }
                    else
                    {
                        VariableBase->DataType = ValueType::Int;
                    }
                }
                else if (Type == "float")
                {
                    VariableBase->DataType = ValueType::Double;
                }
                else if (Type == "string")
                {
                    VariableBase->DataType = ValueType::String;
                }

                if (bShouldSave)
                {
                    auto VariableSaved = VariableSavedStruct{};
                    VariableSaved.Namespace = NamespaceName;
                    VariableSaved.Name = VariableName;
                    VariableSaved.QVariableBase = VariableBase;
                    VariableSaved.PreValue = "";

                    NeedSaveVariables.append(VariableSaved);
                }

                if (!ValueTableJV.isUndefined())
                {
                    QJsonArray ValueTableArr = ValueTableJV.toArray();
                    for (auto ValueTableRef : ValueTableArr)
                    {
                        QJsonObject ValueTableObj = ValueTableRef.toObject();
                        ValueTable TempValue;

                        QString DisplayString = ValueTableObj.value("displayString").toString();
                        QString Value = ValueTableObj.value("value").toString();

                        TempValue.DisplayName = DisplayString;
                        TempValue.Value = Value.toInt();

                        VariableBase->ValueTables.append(TempValue);
                    }
                }

                Variable.Variables.insert(VariableName, VariableBase);
            }

            Variables.insert(NamespaceName, Variable);
        }
    }
}

void QSystemVariables::InitConfig()
{
    if (CurrentType == CustomEnum::None)
    {
        return;
    }

    QFile file(FullFilePath);
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);

    file.close();

    qDebug() << "Create File" << FullFilePath;
}

void QSystemVariables::SaveConfig(const QJsonDocument& doc) const
{
    QFile file(FullFilePath);
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);

    QTextStream stream(&file);
    stream << doc.toJson();
    file.close();
}

CustomEnum::EFormType QSystemVariables::GetCurrentType() const
{
    return CurrentType;
}

void QSystemVariables::SetCurrentType(const CustomEnum::EFormType CurrentType)
{
    this->CurrentType = CurrentType;
}

bool QSystemVariables::IsValidNamespaceAndName(const QString& Namespace, const QString& Name)
{
    if (!Variables.contains(Namespace))
    {
        qDebug() << "Namespace:" << Namespace << "Not Found!";
        return false;
    }

    if (!Variables.value(Namespace).Variables.contains(Name))
    {
        qDebug() << "Variable:" << Namespace << ":" << Name << "Not Found!";
        return false;
    }

    return true;
}

QList<ValueTable> QSystemVariables::GetVariablesByNamespaceAndName(const QString& Namespace, const QString& Name)
{
    QList<ValueTable> Result;

    if (const auto VariableBase = GetVariableBaseByNamespaceAndName(Namespace, Name))
    {
        Result = VariableBase->ValueTables;
    }

    return Result;
}

QVariableBase* QSystemVariables::GetVariableBaseByNamespaceAndName(const QString& Namespace, const QString& Name)
{
    QVariableBase* Result = nullptr;

    if (IsValidNamespaceAndName(Namespace, Name))
    {
        Result = Variables.value(Namespace).Variables.value(Name);
    }

    return Result;
}

int GetTableValueByIndex(const QList<ValueTable>& InValueTable, const int Index)
{
    if (InValueTable.length() <= Index) return -1;

    return InValueTable[Index].Value;
}

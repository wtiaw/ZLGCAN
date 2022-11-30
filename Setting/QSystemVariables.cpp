#include "QSystemVariables.h"

#include <qjsonarray.h>

QMultiMap<QString, VariableNamespace> QSystemVariables::Variables;

QSystemVariables::QSystemVariables([[maybe_unused]] QObject* parent)
{
    ConfigDirPath += "/SystemVariables";
    SetConfigFilePath("SystemVariables");
}

void QSystemVariables::ReadConfig()
{
    if (const QDir dir(ConfigDirPath); !dir.exists())
    {
        if (const bool ismkdir = dir.mkdir(ConfigDirPath); !ismkdir)
            qDebug() << "Create path fail" << Qt::endl;
        else
            qDebug() << "Create full path success" << Qt::endl;
    }
    
    if (const QFileInfo fi(FullFilePath); !fi.isFile())
    {
        InitConfig();
        return;
    }

    QFile file(FullFilePath);
    qDebug() << "ReadConfig" << FullFilePath;
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "can't open error!";
        return;
    }

    // 读取文件的全部内容
    QTextStream stream(&file);
    const QString str = stream.readAll();

    file.close();

    // QJsonParseError类用于在JSON解析期间报告错误。
    QJsonParseError jsonError;
    // 将json解析为UTF-8编码的json文档，并从中创建一个QJsonDocument。
    // 如果解析成功，返回QJsonDocument对象，否则返回null
    const QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8(), &jsonError);
    // 判断是否解析失败
    if (jsonError.error != QJsonParseError::NoError && !doc.isNull())
    {
        qDebug() << "Json格式错误！" << jsonError.error;
        return;
    }

    QMultiMap<QString, VariableNamespace> temp;
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
        VariableNamespace Variable;

        if (NamespaceValueChild.type() == QJsonValue::Object)
        {
            QJsonObject NamespaceObj = NamespaceValueChild.toObject();

            //命名空间
            QString NamespaceName = NamespaceObj.value("name").toString();

            //变量
            QJsonArray VariableArr = NamespaceObj.value("variable").toArray();
            for (auto VariableRef : VariableArr)
            {
                VariableStruct VariableStruct;
                QJsonObject VariableObj = VariableRef.toObject();

                QString VariableName = VariableObj.value("name").toString();
                QString BitCount = VariableObj.value("bitcount").toString();
                QString IsSigned = VariableObj.value("isSigned").toString();
                QString Type = VariableObj.value("type").toString();
                QString Comment;
                QString StartValue;
                QString MaxValue;
                QString MinValue;


                QJsonValue StartValueJV = VariableObj.value("startValue");
                QJsonValue MaxValueJV = VariableObj.value("maxValue");
                QJsonValue MinValueJV = VariableObj.value("minValue");
                QJsonValue CommentJV = VariableObj.value("comment");
                QJsonValue ValueTableJV = VariableObj.value("valuetable");

                if (!StartValueJV.isUndefined())
                {
                    StartValue = StartValueJV.toString();
                    VariableStruct.bHasInitialValue = true;

                    VariableStruct.InitialValue = StartValue;
                }

                if (!MaxValueJV.isUndefined())
                {
                    MaxValue = MaxValueJV.toString();
                    VariableStruct.bHasMax = true;

                    VariableStruct.Max = MaxValue;
                }

                if (!MinValueJV.isUndefined())
                {
                    MinValue = MinValueJV.toString();
                    VariableStruct.bHasMin = true;

                    VariableStruct.Min = MinValue;
                }

                if (!CommentJV.isUndefined())
                {
                    Comment = CommentJV.toString();
                    VariableStruct.bHasComment = true;

                    VariableStruct.Comment = Comment;
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
                        VariableStruct.DataType = EDataType::UInt32;
                    }
                    else
                    {
                        VariableStruct.DataType = EDataType::Int32;
                    }
                }
                else if (Type == "float")
                {
                    VariableStruct.DataType = EDataType::Double;
                }
                else if (Type == "string")
                {
                    VariableStruct.DataType = EDataType::String;
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

                        VariableStruct.ValueTables.append(TempValue);
                    }
                }

                Variable.Variables.insert(VariableName, VariableStruct);
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

#include "LoadVariablesWindow.h"
#include "ui_LoadVariablesWindow.h"
#include <QFileDialog>
#include <qjsonarray.h>
#include <qmetaobject.h>
#include <QScrollBar>
#include <qstack.h>
#include <qstandarditemmodel.h>
#include <qtconcurrentrun.h>

#include "mainwindow.h"
#include "Library/QWidgetLibrary.h"
#include "Setting/QSystemVariables.h"

#define NAME_COLUMN       0
#define DATA_TYPE_COLUMN  1
#define INITIAL_COLUMN    2
#define MIN_COLUMN        3
#define MAX_COLUMN        4
#define COMMENT_COLUMN    5

LoadVariablesWindow::LoadVariablesWindow(QWidget* parent, Qt::WindowFlags f) :
    QWidget(parent, f),
    ui(new Ui::LoadVariablesWindow)
{
    ui->setupUi(this);

    mainWindow = qobject_cast<MainWindow*>(parent);

    setAttribute(Qt::WA_QuitOnClose, false);


    ui->VariableViewer->setColumnWidth(0, 200);
    ui->VariableViewer->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->VariableViewer->header()->setSortIndicator(0, Qt::AscendingOrder);
    //表头加粗
    QFont font = ui->VariableViewer->header()->font();
    font.setBold(true);
    ui->VariableViewer->header()->setFont(font);

    connect(ui->LoadVariables, &QPushButton::clicked, this, &LoadVariablesWindow::On_LoadVariablesClicked);
    connect(ui->SelectPath, &QPushButton::clicked, this, &LoadVariablesWindow::On_SelectPathClicked);

    connect(ui->VariableViewer, &QTreeWidget::clicked, this, &LoadVariablesWindow::TreeClicked);
    connect(ui->VariableViewer, &QTreeWidget::collapsed, this, &LoadVariablesWindow::TreeClicked);
    connect(ui->VariableViewer, &QTreeWidget::expanded, this, &LoadVariablesWindow::expanded);

    connect(ui->VariableViewer, &QTreeWidget::itemClicked, this, &LoadVariablesWindow::ItemClicked);
}

LoadVariablesWindow::~LoadVariablesWindow()
{
    delete ui;
}

void LoadVariablesWindow::ChangeWindowType()
{
    const CustomEnum::EFormType type = MainWindow::SystemVariablesConfig->GetCurrentType();
    const QMetaEnum metaEnum = QMetaEnum::fromType<CustomEnum::EFormType>();
    const QString Name = metaEnum.valueToKey(type);

    setWindowTitle(QString("加载变量 [%1]").arg(Name));

    ShowData();
}

void LoadVariablesWindow::ShowData()
{
    QWidgetLibrary::ClearTreeWidgetChildrenWidget(ui->VariableViewer);

    for (const auto& Key : QSystemVariables::Variables.keys())
    {
        // auto model = new QStandardItemModel(ui->VariableViewer);
        auto* topItem = new QTreeWidgetItem(ui->VariableViewer);
        topItem->setText(NAME_COLUMN, Key);
        ui->VariableViewer->addTopLevelItem(topItem);
        topItem->setCheckState(0, Qt::Unchecked);

        QTreeWidgetItem* CurrentVariableItem = nullptr;
        for (const auto& Namespace : QSystemVariables::Variables.value(Key).Variables.keys())
        {
            const auto Variable = QSystemVariables::Variables.value(Key).Variables.value(Namespace);
            const bool bShouldSave = Variable->bShouldSave;
            const ValueType Type = Variable->DataType;
            QString DisplayType;
            QString StartValue;
            QString MinValue;
            QString MaxValue;
            QString Comment = Variable->Comment;

            StartValue = Variable->InitialValue;
            MinValue = Variable->MinValue;
            MaxValue = Variable->MaxValue;

            switch (Type)
            {
            case ValueType::Int:
                DisplayType = "int32";
                break;

            case ValueType::UInt:
                DisplayType = "uint32";
                break;

            case ValueType::Double:
                DisplayType = "double";
                break;

            case ValueType::String:
                DisplayType = "string";
                break;
            }

            if (!Variable->bHasComment)
            {
                Comment = "-";
            }

            if (!Variable->bHasMax)
            {
                MaxValue = "-";
            }

            if (!Variable->bHasMin)
            {
                MinValue = "-";
            }

            if (!Variable->bHasInitialValue)
            {
                StartValue = "-";
            }


            CurrentVariableItem = new QTreeWidgetItem(topItem);
            SetItemData(CurrentVariableItem, Namespace, DisplayType, StartValue, MinValue, MaxValue, Comment);

            CurrentVariableItem->setCheckState(0, bShouldSave ? Qt::Checked : Qt::Unchecked);

            if (Variable->ValueTables.count() > 0)
            {
                const auto Widget = new QWidget;
                const auto HBoxLayout = new QHBoxLayout;
                const auto TableWidget = new QTableWidget;

                Widget->setLayout(HBoxLayout);
                HBoxLayout->setContentsMargins(0, 0, 0, 0);
                HBoxLayout->addWidget(TableWidget);
                HBoxLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));

                TableWidget->setColumnCount(2);
                QStringList strs = {"Value", "DisplayName"};
                TableWidget->setHorizontalHeaderLabels(strs);
                TableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
                // TableWidget->setSizeIncrement()
                // TableWidget->horizontalHeader()->setMinimumSectionSize(40); //设置最小列宽
                // TableWidget->setColumnWidth(0, 40);
                TableWidget->verticalHeader()->hide();
                TableWidget->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustToContents);
                TableWidget->horizontalScrollBar()->hide();
                TableWidget->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
                // TableWidget->setMinimumSize(QSize(100,100));
                TableWidget->setMaximumSize(QSize(10000, 150));

                const auto CurrentValueTable = new QTreeWidgetItem(CurrentVariableItem);
                CurrentValueTable->setFirstColumnSpanned(true);


                for (const auto& TableValue : Variable->ValueTables)
                {
                    const QString DisplayName = TableValue.DisplayName;
                    const QString Value = QString("%1").arg(TableValue.Value, 2, 16, QLatin1Char('0')).toUpper();
                    const QString VariableName = QString("0x%1").arg(Value);

                    const int Row = TableWidget->rowCount();
                    TableWidget->insertRow(Row);
                    TableWidget->setItem(Row, 1, new QTableWidgetItem(DisplayName));
                    TableWidget->setItem(Row, 0, new QTableWidgetItem(VariableName));
                }

                ui->VariableViewer->setItemWidget(CurrentValueTable, 0, Widget);
            }
        }

        UpdateParentItem(CurrentVariableItem);
    }
}

void LoadVariablesWindow::SetVariableName(const QMap<QString, QString>& KeyValue,
                                          QJsonObject& VariableObj)
{
    if (!KeyValue.contains("name")) return;

    const QString VariableName = KeyValue["name"];

    VariableObj.insert("name", VariableName);
}

void LoadVariablesWindow::SetVariableDatatype(const QMap<QString, QString>& KeyValue,
                                              QJsonObject& VariableObj)
{
    if (!KeyValue.contains("bitcount")) return;
    if (!KeyValue.contains("isSigned")) return;
    if (!KeyValue.contains("type")) return;

    const QString BitCount = KeyValue["bitcount"];
    const QString IsSigned = KeyValue["isSigned"];
    const QString Type = KeyValue["type"];

    VariableObj.insert("type", Type);
    VariableObj.insert("isSigned", IsSigned);
    VariableObj.insert("bitcount", BitCount);
}

void LoadVariablesWindow::SetVariableStartValue(const QMap<QString, QString>& KeyValue,
                                                QJsonObject& VariableObj)
{
    if (!KeyValue.contains("startValue"))
    {
        return;
    }

    const QString StartValue = KeyValue["startValue"];

    VariableObj.insert("startValue", StartValue);
}

void LoadVariablesWindow::SetVariableMinValue(const QMap<QString, QString>& KeyValue,
                                              QJsonObject& VariableObj)
{
    if (!KeyValue.contains("minValue"))
    {
        return;
    }

    const QString MinValue = KeyValue["minValue"];

    VariableObj.insert("minValue", MinValue);
}

void LoadVariablesWindow::SetVariableMaxValue(const QMap<QString, QString>& KeyValue,
                                              QJsonObject& VariableObj)
{
    if (!KeyValue.contains("maxValue"))
    {
        return;
    }

    const QString MaxValue = KeyValue["maxValue"];

    VariableObj.insert("maxValue", MaxValue);
}

void LoadVariablesWindow::SetVariableComment(const QMap<QString, QString>& KeyValue,
                                             QJsonObject& VariableObj)
{
    if (!KeyValue.contains("comment"))
    {
        return;
    }

    if (KeyValue["comment"] == "")
    {
        return;
    }

    const QString Comment = KeyValue["comment"];

    VariableObj.insert("comment", Comment);
}

void LoadVariablesWindow::SetValueTableName(const QMap<QString, QString>& KeyValue,
                                            QJsonObject& VariableObj)
{
    if (!KeyValue.contains("displayString")) return;

    const QString VariableName = KeyValue["displayString"];

    VariableObj.insert("displayString", VariableName);
}

void LoadVariablesWindow::SetValueTableValue(const QMap<QString, QString>& KeyValue,
                                             QJsonObject& VariableObj)
{
    if (!KeyValue.contains("value")) return;

    VariableObj.insert("value", KeyValue["value"]);
}

void LoadVariablesWindow::SetItemData(QTreeWidgetItem* CurrentItem, const QString& Namespace,
                                      const QString& DisplayType, const QString& StartValue, const QString& MinValue,
                                      const QString& MaxValue, const QString& Comment)
{
    CurrentItem->setText(NAME_COLUMN, Namespace);
    CurrentItem->setText(DATA_TYPE_COLUMN, DisplayType);
    CurrentItem->setText(INITIAL_COLUMN, StartValue);
    CurrentItem->setText(MIN_COLUMN, MinValue);
    CurrentItem->setText(MAX_COLUMN, MaxValue);
    CurrentItem->setText(COMMENT_COLUMN, Comment);
}

void LoadVariablesWindow::UpdateParentItem(const QTreeWidgetItem* item)
{
    QTreeWidgetItem* parent = item->parent();
    if (parent == nullptr)
    {
        return;
    }
    //选中的子节点个数
    int selectedCount = 0;
    const int childCount = parent->childCount();
    for (int i = 0; i < childCount; i++)
    {
        if (const QTreeWidgetItem* childItem = parent->child(i); childItem->checkState(0) == Qt::Checked)
        {
            selectedCount++;
        }
    }
    if (selectedCount <= 0)
    {
        //未选中状态
        parent->setCheckState(0, Qt::Unchecked);
    }
    else if (selectedCount > 0 && selectedCount < childCount)
    {
        //部分选中状态
        parent->setCheckState(0, Qt::PartiallyChecked);
    }
    else if (selectedCount == childCount)
    {
        //选中状态
        parent->setCheckState(0, Qt::Checked);
    }
}

QString LoadVariablesWindow::GetTopLevelItemDisplayName(const QTreeWidgetItem* CurrentItem)
{
    QString Res;
    const QTreeWidgetItem* TopItem = CurrentItem;
    while (TopItem->parent())
    {
        TopItem = TopItem->parent();
    }

    for (int i = 0; i < TopItem->treeWidget()->topLevelItemCount(); i++)
    {
        if (TopItem == TopItem->treeWidget()->topLevelItem(i))
        {
            Res = TopItem->text(0);
            break;
        }
    }

    return Res;
}

void LoadVariablesWindow::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);

    ChangeWindowType();
}

void LoadVariablesWindow::On_LoadVariablesClicked()
{
    // QFuture<void> future = QtConcurrent::run(
    //     [=]()
    //     {
    if (FilePath == "")
    {
        return;
    }

    QMultiMap<QString, VariableNamespacePair> temp;
    QSystemVariables::Variables.swap(temp);
    QFile File(FilePath);

    if (!File.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug("文件打开失败");
        return;
    }
    QTextStream ReadStream(&File);

    QTreeWidgetItem* CurrentNamespaceItem = nullptr;
    QTreeWidgetItem* CurrentVariableItem = nullptr;

    QJsonArray NamespaceArray;
    QJsonArray VariableArray;
    QJsonArray ValueTableArray;

    QJsonObject RootObj;
    QJsonObject NamespaceObj;
    QJsonObject VariableObj;

    int NamespaceCount = 0;
    while (!ReadStream.atEnd())
    {
        int index = 0;
        QString Text = ReadStream.readLine();
        QString TagStr;

        while (index < Text.length())
        {
            QChar ch = Text[index];

            if (ch != '<')
            {
                index ++;
            }
            else
            {
                break;
            }
        }

        if (index == Text.length()) continue;

        index++;
        while (Text[index] != '>')
        {
            TagStr += Text[index++];
        }

        QStringList strList = TagStr.split(" ");

        // if (strList.length() < 2) continue;

        QMap<QString, QString> KeyValue;
        for (int i = 1; i < strList.length(); ++i)
        {
            QStringList KeyValueStr = strList[i].replace("\"", "").split("=");

            if (KeyValueStr.length() < 2)
            {
                break;
            }

            KeyValue.insert(KeyValueStr[0], KeyValueStr[1]);
        }


        if (strList[0] == "namespace")
        {
            if (++NamespaceCount < 1) continue;

            QString Name = KeyValue["name"];
            auto* topItem = new QTreeWidgetItem(ui->VariableViewer);
            topItem->setText(NAME_COLUMN, Name);
            ui->VariableViewer->addTopLevelItem(topItem);

            NamespaceObj.insert("name", Name);
            CurrentNamespaceItem = topItem;
        }
        else if (strList[0] == "/namespace")
        {
            if (--NamespaceCount < 1) continue;

            std::sort(VariableArray.begin(), VariableArray.end(), [](const QJsonValue& v1, const QJsonValue& v2)
            {
                return v1.toObject()["name"].toString() < v2.toObject()["name"].toString();
            });

            NamespaceObj.insert("variable", VariableArray);
            NamespaceArray.append(NamespaceObj);

            while (!VariableArray.empty())
            {
                VariableArray.removeFirst();
            }

            CurrentNamespaceItem = nullptr;
        }
        else if (strList[0] == "variable")
        {
            QJsonObject VariableTempObj;
            CurrentVariableItem = new QTreeWidgetItem(CurrentNamespaceItem);

            //Name
            SetVariableName(KeyValue, VariableTempObj);

            //-----------------------------数据类型-----------------------------//
            SetVariableDatatype(KeyValue, VariableTempObj);

            //-----------------------------初始值-----------------------------//
            SetVariableStartValue(KeyValue, VariableTempObj);

            //-----------------------------最小值-----------------------------//
            SetVariableMinValue(KeyValue, VariableTempObj);

            //-----------------------------最大值-----------------------------//
            SetVariableMaxValue(KeyValue, VariableTempObj);

            //-----------------------------注释-----------------------------//
            SetVariableComment(KeyValue, VariableTempObj);

            VariableTempObj.insert("shouldSave", false);

            VariableArray.append(VariableTempObj);
            VariableObj = VariableTempObj;
        }
        else if (strList[0] == "valuetableentry")
        {
            QJsonObject ValueTableObj;

            SetValueTableName(KeyValue, ValueTableObj);
            SetValueTableValue(KeyValue, ValueTableObj);

            ValueTableArray.append(ValueTableObj);
            new QTreeWidgetItem(CurrentVariableItem);
        }
        else if (strList[0] == "/valuetable")
        {
            std::sort(ValueTableArray.begin(), ValueTableArray.end(), [](const QJsonValue& v1, const QJsonValue& v2)
            {
                return v1.toObject()["value"].toInt() < v2.toObject()["value"].toInt();
            });

            VariableObj.insert("valuetable", ValueTableArray);
            VariableArray.removeLast();
            VariableArray.append(VariableObj);

            while (!ValueTableArray.empty())
            {
                ValueTableArray.removeFirst();
            }
        }
    }

    std::sort(NamespaceArray.begin(), NamespaceArray.end(), [](const QJsonValue& v1, const QJsonValue& v2)
    {
        return v1.toObject()["name"].toString() < v2.toObject()["name"].toString();
    });

    RootObj.insert("namespace", NamespaceArray);
    // 将json对象里的数据转换为字符串
    QJsonDocument doc;
    // 将object设置为本文档的主要对象
    doc.setObject(RootObj);

    // ui->VariableViewer->header()->setSortIndicator(0, Qt::AscendingOrder);
    mainWindow->SystemVariablesConfig->SaveConfig(doc);
    mainWindow->SystemVariablesConfig->ReadConfig();

    ShowData();
}

void LoadVariablesWindow::On_SelectPathClicked()
{
    auto* FileDialog = new QFileDialog(this);
    FileDialog->setWindowTitle("加载变量");
    FileDialog->setNameFilter("File(*.cfg;*.json)");
    FileDialog->setViewMode(QFileDialog::Detail);

    if (FileDialog->exec() == QDialog::Accepted)
    {
        FilePath = FileDialog->selectedFiles()[0];
        ui->Path->setText(FilePath);
    }
}

void LoadVariablesWindow::TreeClicked(const QModelIndex& index)
{
    ui->VariableViewer->resizeColumnToContents(5);
}

void LoadVariablesWindow::expanded(const QModelIndex& index)
{
    ui->VariableViewer->resizeColumnToContents(5);
    // ui->VariableViewer->header()->setSortIndicator(2, Qt::AscendingOrder);
}

void LoadVariablesWindow::ItemClicked(const QTreeWidgetItem* item)
{
    const int cnt = item->childCount();

    QJsonObject rootObj = QSystemVariables::doc.object();
    const QJsonValue NamespaceValue = rootObj.value("namespace");
    QJsonArray NamespaceArray = NamespaceValue.toArray();
    QJsonObject Variable;
    int Count = 0;
    for (int i = 0; i < NamespaceArray.size(); i++)
    {
        if (auto temp = NamespaceArray[i].toObject(); temp["name"] == GetTopLevelItemDisplayName(item))
        {
            Count = i;
            Variable = temp;
        }
    }
    
    if (Variable.isEmpty())
    {
        return;
    }

    QJsonArray Variables = Variable["variable"].toArray();

    if (cnt > 0 && !ui->VariableViewer->itemWidget(item->child(0), 0))
    {
        for (int i = 0; i < cnt; i++)
        {
            item->child(i)->setCheckState(0, item->checkState(0));

            QJsonObject Var = Variables[i].toObject();

            Var["shouldSave"] = item->checkState(0) ? true : false;

            Variables.replace(i, Var);
        }
    }
    else
    {
        QJsonObject Var;
        int RowCount = 0;
        for (int i = 0 ; i < Variables.size(); i++)
        {
            if (auto temp = Variables[i].toObject(); temp["name"] == item->text(0))
            {
                RowCount = i;
                Var = temp;
            }
        }

        if (Var.isEmpty())
        {
            return;
        }

        Var["shouldSave"] = item->checkState(0) ? true : false;

        Variables.replace(RowCount, Var);
    }

    Variable["variable"] = Variables;
    NamespaceArray.replace(Count, Variable);
    rootObj["namespace"] = NamespaceArray;
    QSystemVariables::doc.setObject(rootObj);

    MainWindow::SystemVariablesConfig->SaveConfig(QSystemVariables::doc);
    MainWindow::SystemVariablesConfig->ReadConfig();
    UpdateParentItem(item);
}

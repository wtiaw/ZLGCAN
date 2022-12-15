#ifndef LOADVARIABLESWINDOW_H
#define LOADVARIABLESWINDOW_H

#include <qjsonvalue.h>
#include <QWidget>

inline void swap(QJsonValueRef v1, QJsonValueRef v2)
{
    QJsonValue temp(v1);
    v1 = QJsonValue(v2);
    v2 = temp;
}

namespace Ui
{
    class LoadVariablesWindow;
}

class LoadVariablesWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoadVariablesWindow(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~LoadVariablesWindow() override;

    void ChangeWindowType();
    void ShowData();

private:
    void SetVariableName(const QMap<QString, QString>& KeyValue, QJsonObject& VariableObj);
    void SetVariableDatatype(const QMap<QString, QString>& KeyValue, QJsonObject& VariableObj);
    void SetVariableStartValue(const QMap<QString, QString>& KeyValue, QJsonObject& VariableObj);
    void SetVariableMinValue(const QMap<QString, QString>& KeyValue, QJsonObject& VariableObj);
    void SetVariableMaxValue(const QMap<QString, QString>& KeyValue, QJsonObject& VariableObj);
    void SetVariableComment(const QMap<QString, QString>& KeyValue, QJsonObject& VariableObj);

    void SetValueTableName(const QMap<QString, QString>& KeyValue, QJsonObject& VariableObj);
    void SetValueTableValue(const QMap<QString, QString>& KeyValue, QJsonObject& VariableObj);

    void SetItemData(class QTreeWidgetItem* CurrentItem, const QString& Namespace = "-",
                     const QString& DisplayType = "-", const QString& StartValue = "-", const QString& MinValue = "-",
                     const QString& MaxValue = "-", const QString& Comment = "-");

    void UpdateParentItem(const QTreeWidgetItem *item);

    QString GetTopLevelItemDisplayName(const class QTreeWidgetItem* CurrentItem);

private slots:
    void showEvent(QShowEvent* event) override;
    
    void On_LoadVariablesClicked();
    void On_SelectPathClicked();

    void TreeClicked(const QModelIndex& index);
    void expanded(const QModelIndex& index);

    void ItemClicked(const QTreeWidgetItem * item);

private:
    Ui::LoadVariablesWindow* ui;

    class MainWindow* mainWindow;

    QString FilePath;
};


#endif // LOADVARIABLESWINDOW_H

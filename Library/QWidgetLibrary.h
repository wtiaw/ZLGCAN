#ifndef QWIDGETLIBRARY_H
#define QWIDGETLIBRARY_H


#include "qlineedit.h"
class QWidgetLibrary
{

public:
    static void ClearLayoutChildrenWidget(class QLayout* InLayout);
    static void ClearTreeWidgetChildrenWidget(const class QTreeWidget* InTreeWidget);

    //获取Edit文本信息
    static QString GetLineTextValue(const class QLineEdit* InLineEdit);

    //检查DLC输入格式
    static bool CheckDLCData(QLineEdit* DLCEditor, const QComboBox* InComboBox);

    static void CreateDataEdit(class QLayout *InLayout, class QLineEdit* DLCEditer, QVector<class DataEdit*> &DataEdits);

    static void InitMessageFrameTypeComboBox(QComboBox* InComboBox);

    static void InitMessageID(QLineEdit* MessageIDEditor);
    static void InitMessageDLC(QLineEdit* DLCEditor);

private:
    static void RemoveItem(const class QTreeWidgetItem *item);
};

#endif // QWIDGETLIBRARY_H

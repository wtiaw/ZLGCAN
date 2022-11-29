/********************************************************************************
** Form generated from reading UI file 'LoadVariablesWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOADVARIABLESWINDOW_H
#define UI_LOADVARIABLESWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoadVariablesWindow
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *Path;
    QPushButton *SelectPath;
    QPushButton *LoadVariables;
    QTreeWidget *VariableViewer;

    void setupUi(QWidget *LoadVariablesWindow)
    {
        if (LoadVariablesWindow->objectName().isEmpty())
            LoadVariablesWindow->setObjectName("LoadVariablesWindow");
        LoadVariablesWindow->resize(700, 700);
        gridLayout = new QGridLayout(LoadVariablesWindow);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        Path = new QLineEdit(LoadVariablesWindow);
        Path->setObjectName("Path");

        horizontalLayout->addWidget(Path);

        SelectPath = new QPushButton(LoadVariablesWindow);
        SelectPath->setObjectName("SelectPath");
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SelectPath->sizePolicy().hasHeightForWidth());
        SelectPath->setSizePolicy(sizePolicy);
        SelectPath->setMaximumSize(QSize(30, 16777215));

        horizontalLayout->addWidget(SelectPath);

        LoadVariables = new QPushButton(LoadVariablesWindow);
        LoadVariables->setObjectName("LoadVariables");

        horizontalLayout->addWidget(LoadVariables);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        VariableViewer = new QTreeWidget(LoadVariablesWindow);
        VariableViewer->setObjectName("VariableViewer");
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(VariableViewer->sizePolicy().hasHeightForWidth());
        VariableViewer->setSizePolicy(sizePolicy1);
        VariableViewer->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        VariableViewer->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        VariableViewer->setSortingEnabled(true);
        VariableViewer->setColumnCount(6);
        VariableViewer->header()->setCascadingSectionResizes(false);
        VariableViewer->header()->setDefaultSectionSize(100);
        VariableViewer->header()->setHighlightSections(false);

        gridLayout->addWidget(VariableViewer, 1, 0, 1, 1);


        retranslateUi(LoadVariablesWindow);

        QMetaObject::connectSlotsByName(LoadVariablesWindow);
    } // setupUi

    void retranslateUi(QWidget *LoadVariablesWindow)
    {
        LoadVariablesWindow->setWindowTitle(QCoreApplication::translate("LoadVariablesWindow", "Form", nullptr));
        SelectPath->setText(QCoreApplication::translate("LoadVariablesWindow", "...", nullptr));
        LoadVariables->setText(QCoreApplication::translate("LoadVariablesWindow", "\345\212\240\350\275\275\345\217\230\351\207\217", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = VariableViewer->headerItem();
        ___qtreewidgetitem->setText(5, QCoreApplication::translate("LoadVariablesWindow", "Comment", nullptr));
        ___qtreewidgetitem->setText(4, QCoreApplication::translate("LoadVariablesWindow", "Max", nullptr));
        ___qtreewidgetitem->setText(3, QCoreApplication::translate("LoadVariablesWindow", "Min", nullptr));
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("LoadVariablesWindow", "Initial Value", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("LoadVariablesWindow", "DataType", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("LoadVariablesWindow", "Variable", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoadVariablesWindow: public Ui_LoadVariablesWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOADVARIABLESWINDOW_H

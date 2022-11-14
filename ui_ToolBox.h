/********************************************************************************
** Form generated from reading UI file 'ToolBox.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOOLBOX_H
#define UI_TOOLBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ToolBox
{
public:
    QGridLayout *gridLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;

    void setupUi(QWidget *ToolBox)
    {
        if (ToolBox->objectName().isEmpty())
            ToolBox->setObjectName("ToolBox");
        ToolBox->resize(400, 300);
        gridLayout = new QGridLayout(ToolBox);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(ToolBox);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 398, 298));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(-1, 0, -1, 0);
        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea, 0, 0, 1, 1);


        retranslateUi(ToolBox);

        QMetaObject::connectSlotsByName(ToolBox);
    } // setupUi

    void retranslateUi(QWidget *ToolBox)
    {
        ToolBox->setWindowTitle(QCoreApplication::translate("ToolBox", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ToolBox: public Ui_ToolBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOOLBOX_H

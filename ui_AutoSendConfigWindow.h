/********************************************************************************
** Form generated from reading UI file 'AutoSendConfigWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTOSENDCONFIGWINDOW_H
#define UI_AUTOSENDCONFIGWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AutoSendConfigWindow
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QPushButton *AddButton;
    QPushButton *DeleteButton;

    void setupUi(QWidget *AutoSendConfigWindow)
    {
        if (AutoSendConfigWindow->objectName().isEmpty())
            AutoSendConfigWindow->setObjectName("AutoSendConfigWindow");
        AutoSendConfigWindow->resize(517, 300);
        verticalLayout = new QVBoxLayout(AutoSendConfigWindow);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(AutoSendConfigWindow);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        AddButton = new QPushButton(AutoSendConfigWindow);
        AddButton->setObjectName("AddButton");
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AddButton->sizePolicy().hasHeightForWidth());
        AddButton->setSizePolicy(sizePolicy);
        AddButton->setMaximumSize(QSize(25, 16777215));

        horizontalLayout->addWidget(AddButton);

        DeleteButton = new QPushButton(AutoSendConfigWindow);
        DeleteButton->setObjectName("DeleteButton");
        DeleteButton->setMaximumSize(QSize(25, 16777215));

        horizontalLayout->addWidget(DeleteButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(AutoSendConfigWindow);

        QMetaObject::connectSlotsByName(AutoSendConfigWindow);
    } // setupUi

    void retranslateUi(QWidget *AutoSendConfigWindow)
    {
        AutoSendConfigWindow->setWindowTitle(QCoreApplication::translate("AutoSendConfigWindow", "Form", nullptr));
        label->setText(QCoreApplication::translate("AutoSendConfigWindow", "\351\205\215\347\275\256", nullptr));
        AddButton->setText(QCoreApplication::translate("AutoSendConfigWindow", "+", nullptr));
        DeleteButton->setText(QCoreApplication::translate("AutoSendConfigWindow", "-", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AutoSendConfigWindow: public Ui_AutoSendConfigWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTOSENDCONFIGWINDOW_H

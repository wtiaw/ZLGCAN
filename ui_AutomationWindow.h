/********************************************************************************
** Form generated from reading UI file 'AutomationWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTOMATIONWINDOW_H
#define UI_AUTOMATIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AutomationWindow
{
public:
    QGridLayout *gridLayout;
    QPushButton *test;

    void setupUi(QWidget *AutomationWindow)
    {
        if (AutomationWindow->objectName().isEmpty())
            AutomationWindow->setObjectName("AutomationWindow");
        AutomationWindow->resize(400, 300);
        gridLayout = new QGridLayout(AutomationWindow);
        gridLayout->setObjectName("gridLayout");
        test = new QPushButton(AutomationWindow);
        test->setObjectName("test");

        gridLayout->addWidget(test, 0, 0, 1, 1);


        retranslateUi(AutomationWindow);

        QMetaObject::connectSlotsByName(AutomationWindow);
    } // setupUi

    void retranslateUi(QWidget *AutomationWindow)
    {
        AutomationWindow->setWindowTitle(QCoreApplication::translate("AutomationWindow", "Form", nullptr));
        test->setText(QCoreApplication::translate("AutomationWindow", "test", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AutomationWindow: public Ui_AutomationWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTOMATIONWINDOW_H

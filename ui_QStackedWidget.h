/********************************************************************************
** Form generated from reading UI file 'QStackedWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QSTACKEDWIDGET_H
#define UI_QSTACKEDWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QStackedWidget
{
public:
    QGridLayout *gridLayout;
    QFrame *Widgets;
    QGridLayout *gridLayout_2;

    void setupUi(QWidget *QStackedWidget)
    {
        if (QStackedWidget->objectName().isEmpty())
            QStackedWidget->setObjectName("QStackedWidget");
        QStackedWidget->resize(400, 300);
        gridLayout = new QGridLayout(QStackedWidget);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        Widgets = new QFrame(QStackedWidget);
        Widgets->setObjectName("Widgets");
        Widgets->setFrameShape(QFrame::StyledPanel);
        Widgets->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(Widgets);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);

        gridLayout->addWidget(Widgets, 0, 0, 1, 1);


        retranslateUi(QStackedWidget);

        QMetaObject::connectSlotsByName(QStackedWidget);
    } // setupUi

    void retranslateUi(QWidget *QStackedWidget)
    {
        QStackedWidget->setWindowTitle(QCoreApplication::translate("QStackedWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QStackedWidget: public Ui_QStackedWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QSTACKEDWIDGET_H

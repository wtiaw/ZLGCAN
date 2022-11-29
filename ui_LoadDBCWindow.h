/********************************************************************************
** Form generated from reading UI file 'LoadDBCWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOADDBCWINDOW_H
#define UI_LOADDBCWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoadDBCWindow
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *Path;
    QPushButton *SelectPath;
    QPushButton *LoadDBC;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *LoadDBCWindow)
    {
        if (LoadDBCWindow->objectName().isEmpty())
            LoadDBCWindow->setObjectName("LoadDBCWindow");
        LoadDBCWindow->resize(400, 300);
        gridLayout = new QGridLayout(LoadDBCWindow);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        Path = new QLineEdit(LoadDBCWindow);
        Path->setObjectName("Path");

        horizontalLayout->addWidget(Path);

        SelectPath = new QPushButton(LoadDBCWindow);
        SelectPath->setObjectName("SelectPath");
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SelectPath->sizePolicy().hasHeightForWidth());
        SelectPath->setSizePolicy(sizePolicy);
        SelectPath->setMaximumSize(QSize(30, 16777215));

        horizontalLayout->addWidget(SelectPath);

        LoadDBC = new QPushButton(LoadDBCWindow);
        LoadDBC->setObjectName("LoadDBC");

        horizontalLayout->addWidget(LoadDBC);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);


        retranslateUi(LoadDBCWindow);

        QMetaObject::connectSlotsByName(LoadDBCWindow);
    } // setupUi

    void retranslateUi(QWidget *LoadDBCWindow)
    {
        LoadDBCWindow->setWindowTitle(QCoreApplication::translate("LoadDBCWindow", "Form", nullptr));
        SelectPath->setText(QCoreApplication::translate("LoadDBCWindow", "...", nullptr));
        LoadDBC->setText(QCoreApplication::translate("LoadDBCWindow", "\345\212\240\350\275\275DBC", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoadDBCWindow: public Ui_LoadDBCWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOADDBCWINDOW_H

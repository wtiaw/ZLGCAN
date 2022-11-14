/********************************************************************************
** Form generated from reading UI file 'ToolPage.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOOLPAGE_H
#define UI_TOOLPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ToolPage
{
public:
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QCheckBox *SelectCheckBox;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QWidget *Title;
    QHBoxLayout *TitleLayout;
    QWidget *verticalLayoutContent_2;
    QVBoxLayout *verticalLayoutContent;
    QWidget *horizontalWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *MessageIDEdit;
    QLabel *label;
    QLineEdit *DLCEdit;
    QLabel *label_3;
    QComboBox *MessageTypeComboBox;
    QSpacerItem *horizontalSpacer;
    QWidget *gridWidget;
    QGridLayout *DataContainer;

    void setupUi(QWidget *ToolPage)
    {
        if (ToolPage->objectName().isEmpty())
            ToolPage->setObjectName("ToolPage");
        ToolPage->resize(400, 264);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ToolPage->sizePolicy().hasHeightForWidth());
        ToolPage->setSizePolicy(sizePolicy);
        horizontalLayout_2 = new QHBoxLayout(ToolPage);
        horizontalLayout_2->setSpacing(5);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(9, 0, 9, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(-1, 5, 0, -1);
        SelectCheckBox = new QCheckBox(ToolPage);
        SelectCheckBox->setObjectName("SelectCheckBox");
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(SelectCheckBox->sizePolicy().hasHeightForWidth());
        SelectCheckBox->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(SelectCheckBox);

        verticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_2->addLayout(verticalLayout);

        groupBox = new QGroupBox(ToolPage);
        groupBox->setObjectName("groupBox");
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy2);
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 2, 0, 2);
        Title = new QWidget(groupBox);
        Title->setObjectName("Title");
        sizePolicy.setHeightForWidth(Title->sizePolicy().hasHeightForWidth());
        Title->setSizePolicy(sizePolicy);
        Title->setMaximumSize(QSize(16777215, 16777215));
        TitleLayout = new QHBoxLayout(Title);
        TitleLayout->setSpacing(0);
        TitleLayout->setObjectName("TitleLayout");
        TitleLayout->setContentsMargins(0, 0, 5, 0);

        verticalLayout_2->addWidget(Title);

        verticalLayoutContent_2 = new QWidget(groupBox);
        verticalLayoutContent_2->setObjectName("verticalLayoutContent_2");
        verticalLayoutContent_2->setEnabled(true);
        verticalLayoutContent = new QVBoxLayout(verticalLayoutContent_2);
        verticalLayoutContent->setSpacing(0);
        verticalLayoutContent->setObjectName("verticalLayoutContent");
        verticalLayoutContent->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayoutContent->setContentsMargins(0, 2, 0, 0);
        horizontalWidget = new QWidget(verticalLayoutContent_2);
        horizontalWidget->setObjectName("horizontalWidget");
        sizePolicy2.setHeightForWidth(horizontalWidget->sizePolicy().hasHeightForWidth());
        horizontalWidget->setSizePolicy(sizePolicy2);
        horizontalLayout = new QHBoxLayout(horizontalWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(-1, 0, -1, 1);
        label_2 = new QLabel(horizontalWidget);
        label_2->setObjectName("label_2");

        horizontalLayout->addWidget(label_2);

        MessageIDEdit = new QLineEdit(horizontalWidget);
        MessageIDEdit->setObjectName("MessageIDEdit");
        MessageIDEdit->setMaximumSize(QSize(30, 16777215));
        MessageIDEdit->setMaxLength(3);
        MessageIDEdit->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(MessageIDEdit);

        label = new QLabel(horizontalWidget);
        label->setObjectName("label");
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label);

        DLCEdit = new QLineEdit(horizontalWidget);
        DLCEdit->setObjectName("DLCEdit");
        DLCEdit->setMaximumSize(QSize(30, 16777215));
        DLCEdit->setMaxLength(2);
        DLCEdit->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(DLCEdit);

        label_3 = new QLabel(horizontalWidget);
        label_3->setObjectName("label_3");

        horizontalLayout->addWidget(label_3);

        MessageTypeComboBox = new QComboBox(horizontalWidget);
        MessageTypeComboBox->setObjectName("MessageTypeComboBox");
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(MessageTypeComboBox->sizePolicy().hasHeightForWidth());
        MessageTypeComboBox->setSizePolicy(sizePolicy3);

        horizontalLayout->addWidget(MessageTypeComboBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayoutContent->addWidget(horizontalWidget);

        gridWidget = new QWidget(verticalLayoutContent_2);
        gridWidget->setObjectName("gridWidget");
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(gridWidget->sizePolicy().hasHeightForWidth());
        gridWidget->setSizePolicy(sizePolicy4);
        DataContainer = new QGridLayout(gridWidget);
        DataContainer->setObjectName("DataContainer");

        verticalLayoutContent->addWidget(gridWidget);


        verticalLayout_2->addWidget(verticalLayoutContent_2);


        horizontalLayout_2->addWidget(groupBox);


        retranslateUi(ToolPage);

        QMetaObject::connectSlotsByName(ToolPage);
    } // setupUi

    void retranslateUi(QWidget *ToolPage)
    {
        ToolPage->setWindowTitle(QCoreApplication::translate("ToolPage", "Form", nullptr));
        SelectCheckBox->setText(QString());
        groupBox->setTitle(QString());
        label_2->setText(QCoreApplication::translate("ToolPage", "ID(0x):", nullptr));
        MessageIDEdit->setPlaceholderText(QCoreApplication::translate("ToolPage", "001", nullptr));
        label->setText(QCoreApplication::translate("ToolPage", "DLC:", nullptr));
        DLCEdit->setPlaceholderText(QCoreApplication::translate("ToolPage", "8", nullptr));
        label_3->setText(QCoreApplication::translate("ToolPage", "\345\215\217\350\256\256:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ToolPage: public Ui_ToolPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOOLPAGE_H

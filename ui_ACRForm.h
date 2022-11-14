/********************************************************************************
** Form generated from reading UI file 'ACRForm.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACRFORM_H
#define UI_ACRFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ACRForm
{
public:
    QFormLayout *formLayout;
    QGroupBox *groupBox_3;
    QFormLayout *formLayout_2;
    QLabel *label_4;
    QLineEdit *ACR_Key;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *ACRCrcChk122;
    QLineEdit *ACRCycCntr122;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLineEdit *Activation_Status;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_4;
    QFormLayout *formLayout_3;
    QLabel *label_11;
    QComboBox *ACR_Req_LH;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_13;
    QLineEdit *VHBH_Phy;
    QHBoxLayout *horizontalLayout;
    QLabel *label_12;
    QLineEdit *VHBL_Phy;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_14;
    QLineEdit *Tem;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_15;
    QLineEdit *CANW;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton_5;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_4;
    QLineEdit *FBL;
    QLabel *label;
    QLineEdit *BSW;
    QLineEdit *SV;
    QLabel *label_3;
    QLabel *label_2;

    void setupUi(QWidget *ACRForm)
    {
        if (ACRForm->objectName().isEmpty())
            ACRForm->setObjectName("ACRForm");
        ACRForm->resize(578, 418);
        formLayout = new QFormLayout(ACRForm);
        formLayout->setObjectName("formLayout");
        groupBox_3 = new QGroupBox(ACRForm);
        groupBox_3->setObjectName("groupBox_3");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        formLayout_2 = new QFormLayout(groupBox_3);
        formLayout_2->setObjectName("formLayout_2");
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName("label_4");

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_4);

        ACR_Key = new QLineEdit(groupBox_3);
        ACR_Key->setObjectName("ACR_Key");
        ACR_Key->setReadOnly(true);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, ACR_Key);

        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName("label_5");

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_5);

        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName("label_6");

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_6);

        ACRCrcChk122 = new QLineEdit(groupBox_3);
        ACRCrcChk122->setObjectName("ACRCrcChk122");
        ACRCrcChk122->setReadOnly(true);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, ACRCrcChk122);

        ACRCycCntr122 = new QLineEdit(groupBox_3);
        ACRCycCntr122->setObjectName("ACRCycCntr122");
        ACRCycCntr122->setReadOnly(true);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, ACRCycCntr122);

        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName("label_7");

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_7);

        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName("label_8");

        formLayout_2->setWidget(4, QFormLayout::LabelRole, label_8);

        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName("label_9");

        formLayout_2->setWidget(5, QFormLayout::LabelRole, label_9);

        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName("label_10");

        formLayout_2->setWidget(6, QFormLayout::LabelRole, label_10);

        Activation_Status = new QLineEdit(groupBox_3);
        Activation_Status->setObjectName("Activation_Status");
        Activation_Status->setReadOnly(true);

        formLayout_2->setWidget(3, QFormLayout::FieldRole, Activation_Status);


        formLayout->setWidget(0, QFormLayout::LabelRole, groupBox_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(-1, 0, -1, -1);
        groupBox_4 = new QGroupBox(ACRForm);
        groupBox_4->setObjectName("groupBox_4");
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy1);
        formLayout_3 = new QFormLayout(groupBox_4);
        formLayout_3->setObjectName("formLayout_3");
        label_11 = new QLabel(groupBox_4);
        label_11->setObjectName("label_11");

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label_11);

        ACR_Req_LH = new QComboBox(groupBox_4);
        ACR_Req_LH->addItem(QString());
        ACR_Req_LH->addItem(QString());
        ACR_Req_LH->addItem(QString());
        ACR_Req_LH->addItem(QString());
        ACR_Req_LH->addItem(QString());
        ACR_Req_LH->addItem(QString());
        ACR_Req_LH->addItem(QString());
        ACR_Req_LH->addItem(QString());
        ACR_Req_LH->addItem(QString());
        ACR_Req_LH->addItem(QString());
        ACR_Req_LH->addItem(QString());
        ACR_Req_LH->addItem(QString());
        ACR_Req_LH->addItem(QString());
        ACR_Req_LH->setObjectName("ACR_Req_LH");

        formLayout_3->setWidget(0, QFormLayout::FieldRole, ACR_Req_LH);


        verticalLayout->addWidget(groupBox_4);

        groupBox_5 = new QGroupBox(ACRForm);
        groupBox_5->setObjectName("groupBox_5");
        gridLayout = new QGridLayout(groupBox_5);
        gridLayout->setObjectName("gridLayout");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(-1, 0, -1, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_13 = new QLabel(groupBox_5);
        label_13->setObjectName("label_13");

        horizontalLayout_2->addWidget(label_13);

        VHBH_Phy = new QLineEdit(groupBox_5);
        VHBH_Phy->setObjectName("VHBH_Phy");

        horizontalLayout_2->addWidget(VHBH_Phy);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(-1, 0, -1, -1);
        label_12 = new QLabel(groupBox_5);
        label_12->setObjectName("label_12");
        sizePolicy1.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(label_12);

        VHBL_Phy = new QLineEdit(groupBox_5);
        VHBL_Phy->setObjectName("VHBL_Phy");

        horizontalLayout->addWidget(VHBL_Phy);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_14 = new QLabel(groupBox_5);
        label_14->setObjectName("label_14");
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy2);
        label_14->setMaximumSize(QSize(500, 16777215));

        horizontalLayout_3->addWidget(label_14);

        Tem = new QLineEdit(groupBox_5);
        Tem->setObjectName("Tem");

        horizontalLayout_3->addWidget(Tem);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_15 = new QLabel(groupBox_5);
        label_15->setObjectName("label_15");

        horizontalLayout_4->addWidget(label_15);

        CANW = new QLineEdit(groupBox_5);
        CANW->setObjectName("CANW");

        horizontalLayout_4->addWidget(CANW);


        verticalLayout_2->addLayout(horizontalLayout_4);


        gridLayout->addLayout(verticalLayout_2, 1, 0, 1, 1);


        verticalLayout->addWidget(groupBox_5);


        formLayout->setLayout(0, QFormLayout::FieldRole, verticalLayout);

        groupBox = new QGroupBox(ACRForm);
        groupBox->setObjectName("groupBox");
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy3);
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName("gridLayout_2");
        pushButton_5 = new QPushButton(groupBox);
        pushButton_5->setObjectName("pushButton_5");

        gridLayout_2->addWidget(pushButton_5, 1, 0, 1, 1);

        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName("pushButton_2");

        gridLayout_2->addWidget(pushButton_2, 0, 1, 1, 1);

        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName("pushButton");

        gridLayout_2->addWidget(pushButton, 0, 0, 1, 1);


        formLayout->setWidget(1, QFormLayout::LabelRole, groupBox);

        groupBox_2 = new QGroupBox(ACRForm);
        groupBox_2->setObjectName("groupBox_2");
        sizePolicy1.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy1);
        gridLayout_4 = new QGridLayout(groupBox_2);
        gridLayout_4->setObjectName("gridLayout_4");
        FBL = new QLineEdit(groupBox_2);
        FBL->setObjectName("FBL");
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(FBL->sizePolicy().hasHeightForWidth());
        FBL->setSizePolicy(sizePolicy4);
        FBL->setMaximumSize(QSize(300, 16777215));
        FBL->setAlignment(Qt::AlignCenter);
        FBL->setReadOnly(true);

        gridLayout_4->addWidget(FBL, 2, 2, 1, 1);

        label = new QLabel(groupBox_2);
        label->setObjectName("label");
        QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy5);

        gridLayout_4->addWidget(label, 0, 1, 1, 1);

        BSW = new QLineEdit(groupBox_2);
        BSW->setObjectName("BSW");
        sizePolicy4.setHeightForWidth(BSW->sizePolicy().hasHeightForWidth());
        BSW->setSizePolicy(sizePolicy4);
        BSW->setMaximumSize(QSize(300, 16777215));
        BSW->setAlignment(Qt::AlignCenter);
        BSW->setReadOnly(true);

        gridLayout_4->addWidget(BSW, 0, 2, 1, 1);

        SV = new QLineEdit(groupBox_2);
        SV->setObjectName("SV");
        sizePolicy4.setHeightForWidth(SV->sizePolicy().hasHeightForWidth());
        SV->setSizePolicy(sizePolicy4);
        SV->setMaximumSize(QSize(300, 16777215));
        SV->setAlignment(Qt::AlignCenter);
        SV->setReadOnly(true);

        gridLayout_4->addWidget(SV, 1, 2, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName("label_3");
        sizePolicy5.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy5);
        label_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_3, 2, 1, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName("label_2");
        sizePolicy5.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy5);
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_2, 1, 1, 1, 1);


        formLayout->setWidget(1, QFormLayout::FieldRole, groupBox_2);


        retranslateUi(ACRForm);

        QMetaObject::connectSlotsByName(ACRForm);
    } // setupUi

    void retranslateUi(QWidget *ACRForm)
    {
        ACRForm->setWindowTitle(QCoreApplication::translate("ACRForm", "Form", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("ACRForm", "ACR_122", nullptr));
        label_4->setText(QCoreApplication::translate("ACRForm", "ACR_Key", nullptr));
        label_5->setText(QCoreApplication::translate("ACRForm", "ACRCrcChk122", nullptr));
        label_6->setText(QCoreApplication::translate("ACRForm", "ACRCycCntr122", nullptr));
        label_7->setText(QCoreApplication::translate("ACRForm", "Activation_Status", nullptr));
        label_8->setText(QCoreApplication::translate("ACRForm", "TextLabel", nullptr));
        label_9->setText(QCoreApplication::translate("ACRForm", "TextLabel", nullptr));
        label_10->setText(QCoreApplication::translate("ACRForm", "TextLabel", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("ACRForm", "ACR_121", nullptr));
        label_11->setText(QCoreApplication::translate("ACRForm", "ACR_Req_LH", nullptr));
        ACR_Req_LH->setItemText(0, QCoreApplication::translate("ACRForm", "No Request", nullptr));
        ACR_Req_LH->setItemText(1, QCoreApplication::translate("ACRForm", "Belt Park", nullptr));
        ACR_Req_LH->setItemText(2, QCoreApplication::translate("ACRForm", "Belt Slack Remove", nullptr));
        ACR_Req_LH->setItemText(3, QCoreApplication::translate("ACRForm", "Haptic Warning Level 1", nullptr));
        ACR_Req_LH->setItemText(4, QCoreApplication::translate("ACRForm", "Haptic Warning Level 2", nullptr));
        ACR_Req_LH->setItemText(5, QCoreApplication::translate("ACRForm", "Haptic Warning Level 3", nullptr));
        ACR_Req_LH->setItemText(6, QCoreApplication::translate("ACRForm", "Retract Activation Level 1", nullptr));
        ACR_Req_LH->setItemText(7, QCoreApplication::translate("ACRForm", "Retract Activation Level 2", nullptr));
        ACR_Req_LH->setItemText(8, QCoreApplication::translate("ACRForm", "Retract Activation Level 3", nullptr));
        ACR_Req_LH->setItemText(9, QCoreApplication::translate("ACRForm", "Retract Activation Level 4", nullptr));
        ACR_Req_LH->setItemText(10, QCoreApplication::translate("ACRForm", "Retract Activation Level 5", nullptr));
        ACR_Req_LH->setItemText(11, QCoreApplication::translate("ACRForm", "Retract Activation Level 6", nullptr));
        ACR_Req_LH->setItemText(12, QCoreApplication::translate("ACRForm", "Retract Activation Level 7", nullptr));

        groupBox_5->setTitle(QCoreApplication::translate("ACRForm", "ACR_Probe", nullptr));
        label_13->setText(QCoreApplication::translate("ACRForm", "VHBH", nullptr));
        label_12->setText(QCoreApplication::translate("ACRForm", "VHBL", nullptr));
        label_14->setText(QCoreApplication::translate("ACRForm", "Tem", nullptr));
        label_15->setText(QCoreApplication::translate("ACRForm", "CANW", nullptr));
        groupBox->setTitle(QCoreApplication::translate("ACRForm", "\346\223\215\344\275\234", nullptr));
        pushButton_5->setText(QCoreApplication::translate("ACRForm", "\350\247\243\351\224\201", nullptr));
        pushButton_2->setText(QCoreApplication::translate("ACRForm", "\347\211\210\346\234\254", nullptr));
        pushButton->setText(QCoreApplication::translate("ACRForm", "\345\224\244\351\206\222", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("ACRForm", "\350\275\257\344\273\266\347\211\210\346\234\254", nullptr));
        label->setText(QCoreApplication::translate("ACRForm", "BSW", nullptr));
        label_3->setText(QCoreApplication::translate("ACRForm", "FBL", nullptr));
        label_2->setText(QCoreApplication::translate("ACRForm", "SV", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ACRForm: public Ui_ACRForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACRFORM_H

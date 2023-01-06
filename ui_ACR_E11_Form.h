/********************************************************************************
** Form generated from reading UI file 'ACR_E11_Form.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACR_E11_FORM_H
#define UI_ACR_E11_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "DataDisplayWidget.h"

QT_BEGIN_NAMESPACE

class Ui_ACR_E11_Form
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QPushButton *BT_UnLock;
    QPushButton *BT_ReadVersion;
    QPushButton *BT_WakeUp;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_5;
    DataDisplayWidget *DD_PollingData3;
    QComboBox *CB_PollingData3;
    QComboBox *CB_PollingData2;
    DataDisplayWidget *DD_PollingData4;
    QComboBox *CB_PollingData4;
    QComboBox *CB_PollingData5;
    DataDisplayWidget *DD_PollingData2;
    QComboBox *CB_PollingData1;
    DataDisplayWidget *DD_PollingData1;
    DataDisplayWidget *DD_PollingData5;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_4;
    DataDisplayWidget *DD_ACR_Key;
    DataDisplayWidget *DD_ACRCrcChk122;
    DataDisplayWidget *DD_ACRCycCntr122;
    DataDisplayWidget *DD_Activation_Status;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_6;
    DataDisplayWidget *DD_BSW;
    DataDisplayWidget *DD_SV;
    DataDisplayWidget *DD_FBL;
    QSpacerItem *verticalSpacer;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_4;
    QFormLayout *formLayout_3;
    QLabel *label_11;
    QComboBox *CB_ACR_Req_LH;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout;
    DataDisplayWidget *DD_HSPD_Phy;
    DataDisplayWidget *DD_CANW_Phy;
    DataDisplayWidget *DD_VHBH_Phy;
    DataDisplayWidget *DD_TEM_Phy;
    DataDisplayWidget *DD_VHBL_Phy;
    DataDisplayWidget *DD_VCC_Phy;
    DataDisplayWidget *DD_VBAT_Phy;
    DataDisplayWidget *DD_CUR_Phy;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *ACR_E11_Form)
    {
        if (ACR_E11_Form->objectName().isEmpty())
            ACR_E11_Form->setObjectName("ACR_E11_Form");
        ACR_E11_Form->resize(716, 561);
        gridLayout_3 = new QGridLayout(ACR_E11_Form);
        gridLayout_3->setObjectName("gridLayout_3");
        groupBox = new QGroupBox(ACR_E11_Form);
        groupBox->setObjectName("groupBox");
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName("gridLayout_2");
        BT_UnLock = new QPushButton(groupBox);
        BT_UnLock->setObjectName("BT_UnLock");

        gridLayout_2->addWidget(BT_UnLock, 1, 0, 1, 1);

        BT_ReadVersion = new QPushButton(groupBox);
        BT_ReadVersion->setObjectName("BT_ReadVersion");

        gridLayout_2->addWidget(BT_ReadVersion, 0, 1, 1, 1);

        BT_WakeUp = new QPushButton(groupBox);
        BT_WakeUp->setObjectName("BT_WakeUp");

        gridLayout_2->addWidget(BT_WakeUp, 0, 0, 1, 1);


        gridLayout_3->addWidget(groupBox, 2, 0, 1, 1);

        groupBox_6 = new QGroupBox(ACR_E11_Form);
        groupBox_6->setObjectName("groupBox_6");
        gridLayout_5 = new QGridLayout(groupBox_6);
        gridLayout_5->setObjectName("gridLayout_5");
        DD_PollingData3 = new DataDisplayWidget(groupBox_6);
        DD_PollingData3->setObjectName("DD_PollingData3");

        gridLayout_5->addWidget(DD_PollingData3, 5, 0, 1, 1);

        CB_PollingData3 = new QComboBox(groupBox_6);
        CB_PollingData3->setObjectName("CB_PollingData3");
        CB_PollingData3->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        gridLayout_5->addWidget(CB_PollingData3, 4, 0, 1, 1);

        CB_PollingData2 = new QComboBox(groupBox_6);
        CB_PollingData2->setObjectName("CB_PollingData2");
        CB_PollingData2->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        gridLayout_5->addWidget(CB_PollingData2, 2, 0, 1, 1);

        DD_PollingData4 = new DataDisplayWidget(groupBox_6);
        DD_PollingData4->setObjectName("DD_PollingData4");
        DD_PollingData4->setProperty("UnitType", QVariant::fromValue(DataDisplayWidget::Null));

        gridLayout_5->addWidget(DD_PollingData4, 7, 0, 1, 1);

        CB_PollingData4 = new QComboBox(groupBox_6);
        CB_PollingData4->setObjectName("CB_PollingData4");
        CB_PollingData4->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        gridLayout_5->addWidget(CB_PollingData4, 6, 0, 1, 1);

        CB_PollingData5 = new QComboBox(groupBox_6);
        CB_PollingData5->setObjectName("CB_PollingData5");
        CB_PollingData5->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        gridLayout_5->addWidget(CB_PollingData5, 8, 0, 1, 1);

        DD_PollingData2 = new DataDisplayWidget(groupBox_6);
        DD_PollingData2->setObjectName("DD_PollingData2");

        gridLayout_5->addWidget(DD_PollingData2, 3, 0, 1, 1);

        CB_PollingData1 = new QComboBox(groupBox_6);
        CB_PollingData1->setObjectName("CB_PollingData1");
        CB_PollingData1->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        gridLayout_5->addWidget(CB_PollingData1, 0, 0, 1, 1);

        DD_PollingData1 = new DataDisplayWidget(groupBox_6);
        DD_PollingData1->setObjectName("DD_PollingData1");

        gridLayout_5->addWidget(DD_PollingData1, 1, 0, 1, 1);

        DD_PollingData5 = new DataDisplayWidget(groupBox_6);
        DD_PollingData5->setObjectName("DD_PollingData5");

        gridLayout_5->addWidget(DD_PollingData5, 9, 0, 1, 1);


        gridLayout_3->addWidget(groupBox_6, 1, 1, 1, 1);

        groupBox_3 = new QGroupBox(ACR_E11_Form);
        groupBox_3->setObjectName("groupBox_3");
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy1);
        groupBox_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        groupBox_3->setFlat(false);
        groupBox_3->setCheckable(false);
        gridLayout_4 = new QGridLayout(groupBox_3);
        gridLayout_4->setObjectName("gridLayout_4");
        DD_ACR_Key = new DataDisplayWidget(groupBox_3);
        DD_ACR_Key->setObjectName("DD_ACR_Key");
        DD_ACR_Key->setProperty("DataDisplayAlignment", QVariant(Qt::AlignLeading));

        gridLayout_4->addWidget(DD_ACR_Key, 0, 0, 1, 1);

        DD_ACRCrcChk122 = new DataDisplayWidget(groupBox_3);
        DD_ACRCrcChk122->setObjectName("DD_ACRCrcChk122");
        DD_ACRCrcChk122->setProperty("DataDisplayAlignment", QVariant(Qt::AlignLeading));

        gridLayout_4->addWidget(DD_ACRCrcChk122, 1, 0, 1, 1);

        DD_ACRCycCntr122 = new DataDisplayWidget(groupBox_3);
        DD_ACRCycCntr122->setObjectName("DD_ACRCycCntr122");
        DD_ACRCycCntr122->setProperty("DataDisplayAlignment", QVariant(Qt::AlignLeading));

        gridLayout_4->addWidget(DD_ACRCycCntr122, 2, 0, 1, 1);

        DD_Activation_Status = new DataDisplayWidget(groupBox_3);
        DD_Activation_Status->setObjectName("DD_Activation_Status");
        DD_Activation_Status->setProperty("MaxLength", QVariant(16777215u));
        DD_Activation_Status->setProperty("DataDisplayAlignment", QVariant(Qt::AlignLeading));

        gridLayout_4->addWidget(DD_Activation_Status, 3, 0, 1, 1);


        gridLayout_3->addWidget(groupBox_3, 0, 1, 1, 1);

        groupBox_2 = new QGroupBox(ACR_E11_Form);
        groupBox_2->setObjectName("groupBox_2");
        sizePolicy1.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy1);
        gridLayout_6 = new QGridLayout(groupBox_2);
        gridLayout_6->setObjectName("gridLayout_6");
        gridLayout_6->setContentsMargins(4, 0, 4, 0);
        DD_BSW = new DataDisplayWidget(groupBox_2);
        DD_BSW->setObjectName("DD_BSW");
        sizePolicy1.setHeightForWidth(DD_BSW->sizePolicy().hasHeightForWidth());
        DD_BSW->setSizePolicy(sizePolicy1);
        DD_BSW->setProperty("UnitType", QVariant::fromValue(DataDisplayWidget::Null));

        gridLayout_6->addWidget(DD_BSW, 0, 0, 1, 1);

        DD_SV = new DataDisplayWidget(groupBox_2);
        DD_SV->setObjectName("DD_SV");
        sizePolicy1.setHeightForWidth(DD_SV->sizePolicy().hasHeightForWidth());
        DD_SV->setSizePolicy(sizePolicy1);
        DD_SV->setProperty("UnitType", QVariant::fromValue(DataDisplayWidget::Null));

        gridLayout_6->addWidget(DD_SV, 1, 0, 1, 1);

        DD_FBL = new DataDisplayWidget(groupBox_2);
        DD_FBL->setObjectName("DD_FBL");
        sizePolicy1.setHeightForWidth(DD_FBL->sizePolicy().hasHeightForWidth());
        DD_FBL->setSizePolicy(sizePolicy1);
        DD_FBL->setProperty("UnitType", QVariant::fromValue(DataDisplayWidget::Null));

        gridLayout_6->addWidget(DD_FBL, 2, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer, 3, 0, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 0, 0, 1, 1);

        widget = new QWidget(ACR_E11_Form);
        widget->setObjectName("widget");
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        groupBox_4 = new QGroupBox(widget);
        groupBox_4->setObjectName("groupBox_4");
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy2);
        formLayout_3 = new QFormLayout(groupBox_4);
        formLayout_3->setObjectName("formLayout_3");
        label_11 = new QLabel(groupBox_4);
        label_11->setObjectName("label_11");

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label_11);

        CB_ACR_Req_LH = new QComboBox(groupBox_4);
        CB_ACR_Req_LH->addItem(QString());
        CB_ACR_Req_LH->addItem(QString());
        CB_ACR_Req_LH->addItem(QString());
        CB_ACR_Req_LH->addItem(QString());
        CB_ACR_Req_LH->addItem(QString());
        CB_ACR_Req_LH->addItem(QString());
        CB_ACR_Req_LH->addItem(QString());
        CB_ACR_Req_LH->addItem(QString());
        CB_ACR_Req_LH->addItem(QString());
        CB_ACR_Req_LH->addItem(QString());
        CB_ACR_Req_LH->addItem(QString());
        CB_ACR_Req_LH->addItem(QString());
        CB_ACR_Req_LH->addItem(QString());
        CB_ACR_Req_LH->setObjectName("CB_ACR_Req_LH");

        formLayout_3->setWidget(0, QFormLayout::FieldRole, CB_ACR_Req_LH);


        verticalLayout->addWidget(groupBox_4);

        groupBox_5 = new QGroupBox(widget);
        groupBox_5->setObjectName("groupBox_5");
        groupBox_5->setMinimumSize(QSize(330, 0));
        gridLayout = new QGridLayout(groupBox_5);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setHorizontalSpacing(6);
        gridLayout->setContentsMargins(4, -1, 4, -1);
        DD_HSPD_Phy = new DataDisplayWidget(groupBox_5);
        DD_HSPD_Phy->setObjectName("DD_HSPD_Phy");
        DD_HSPD_Phy->setProperty("MaxLength", QVariant(70u));
        DD_HSPD_Phy->setProperty("UnitType", QVariant::fromValue(DataDisplayWidget::RPM));

        gridLayout->addWidget(DD_HSPD_Phy, 3, 1, 1, 1);

        DD_CANW_Phy = new DataDisplayWidget(groupBox_5);
        DD_CANW_Phy->setObjectName("DD_CANW_Phy");
        DD_CANW_Phy->setProperty("MaxLength", QVariant(70u));
        DD_CANW_Phy->setProperty("UnitType", QVariant::fromValue(DataDisplayWidget::MilliVolt));

        gridLayout->addWidget(DD_CANW_Phy, 3, 0, 1, 1);

        DD_VHBH_Phy = new DataDisplayWidget(groupBox_5);
        DD_VHBH_Phy->setObjectName("DD_VHBH_Phy");
        DD_VHBH_Phy->setProperty("MaxLength", QVariant(70u));
        DD_VHBH_Phy->setProperty("UnitType", QVariant::fromValue(DataDisplayWidget::MilliVolt));

        gridLayout->addWidget(DD_VHBH_Phy, 1, 0, 1, 1);

        DD_TEM_Phy = new DataDisplayWidget(groupBox_5);
        DD_TEM_Phy->setObjectName("DD_TEM_Phy");
        DD_TEM_Phy->setProperty("MaxLength", QVariant(70u));
        DD_TEM_Phy->setProperty("UnitType", QVariant::fromValue(DataDisplayWidget::Celsius));

        gridLayout->addWidget(DD_TEM_Phy, 1, 1, 1, 1);

        DD_VHBL_Phy = new DataDisplayWidget(groupBox_5);
        DD_VHBL_Phy->setObjectName("DD_VHBL_Phy");
        DD_VHBL_Phy->setProperty("MaxLength", QVariant(70u));
        DD_VHBL_Phy->setProperty("UnitType", QVariant::fromValue(DataDisplayWidget::MilliVolt));

        gridLayout->addWidget(DD_VHBL_Phy, 2, 0, 1, 1);

        DD_VCC_Phy = new DataDisplayWidget(groupBox_5);
        DD_VCC_Phy->setObjectName("DD_VCC_Phy");
        DD_VCC_Phy->setProperty("MaxLength", QVariant(70u));
        DD_VCC_Phy->setProperty("UnitType", QVariant::fromValue(DataDisplayWidget::MilliVolt));

        gridLayout->addWidget(DD_VCC_Phy, 0, 0, 1, 1);

        DD_VBAT_Phy = new DataDisplayWidget(groupBox_5);
        DD_VBAT_Phy->setObjectName("DD_VBAT_Phy");
        DD_VBAT_Phy->setProperty("MaxLength", QVariant(70u));
        DD_VBAT_Phy->setProperty("UnitType", QVariant::fromValue(DataDisplayWidget::MilliVolt));

        gridLayout->addWidget(DD_VBAT_Phy, 0, 1, 1, 1);

        DD_CUR_Phy = new DataDisplayWidget(groupBox_5);
        DD_CUR_Phy->setObjectName("DD_CUR_Phy");
        DD_CUR_Phy->setProperty("MaxLength", QVariant(70u));
        DD_CUR_Phy->setProperty("UnitType", QVariant::fromValue(DataDisplayWidget::Ampere));

        gridLayout->addWidget(DD_CUR_Phy, 2, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 4, 0, 1, 1);


        verticalLayout->addWidget(groupBox_5);


        gridLayout_3->addWidget(widget, 1, 0, 1, 1);


        retranslateUi(ACR_E11_Form);

        QMetaObject::connectSlotsByName(ACR_E11_Form);
    } // setupUi

    void retranslateUi(QWidget *ACR_E11_Form)
    {
        ACR_E11_Form->setWindowTitle(QCoreApplication::translate("ACR_E11_Form", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("ACR_E11_Form", "\346\223\215\344\275\234", nullptr));
        BT_UnLock->setText(QCoreApplication::translate("ACR_E11_Form", "\350\247\243\351\224\201", nullptr));
        BT_ReadVersion->setText(QCoreApplication::translate("ACR_E11_Form", "\350\257\273\345\217\226\347\211\210\346\234\254", nullptr));
        BT_WakeUp->setText(QCoreApplication::translate("ACR_E11_Form", "\345\224\244\351\206\222", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("ACR_E11_Form", "PTMP_Polling", nullptr));
        DD_PollingData3->setProperty("DataDisplayName", QVariant(QCoreApplication::translate("ACR_E11_Form", "Polling Data", nullptr)));
        DD_PollingData3->setProperty("DataDisplay", QVariant(QCoreApplication::translate("ACR_E11_Form", "---", nullptr)));
        DD_PollingData4->setProperty("DataDisplayName", QVariant(QCoreApplication::translate("ACR_E11_Form", "Polling Data", nullptr)));
        DD_PollingData4->setProperty("DataDisplay", QVariant(QCoreApplication::translate("ACR_E11_Form", "---", nullptr)));
        DD_PollingData2->setProperty("DataDisplayName", QVariant(QCoreApplication::translate("ACR_E11_Form", "Polling Data", nullptr)));
        DD_PollingData2->setProperty("DataDisplay", QVariant(QCoreApplication::translate("ACR_E11_Form", "---", nullptr)));
        DD_PollingData1->setProperty("DataDisplayName", QVariant(QCoreApplication::translate("ACR_E11_Form", "Polling Data", nullptr)));
        DD_PollingData1->setProperty("DataDisplay", QVariant(QCoreApplication::translate("ACR_E11_Form", "---", nullptr)));
        DD_PollingData5->setProperty("DataDisplayName", QVariant(QCoreApplication::translate("ACR_E11_Form", "Polling Data", nullptr)));
        DD_PollingData5->setProperty("DataDisplay", QVariant(QCoreApplication::translate("ACR_E11_Form", "---", nullptr)));
        groupBox_3->setTitle(QCoreApplication::translate("ACR_E11_Form", "ACR_122", nullptr));
        DD_ACR_Key->setProperty("DataDisplayName", QVariant(QCoreApplication::translate("ACR_E11_Form", "ACR_Key", nullptr)));
        DD_ACRCrcChk122->setProperty("DataDisplayName", QVariant(QCoreApplication::translate("ACR_E11_Form", "ACRCrcChk122", nullptr)));
        DD_ACRCycCntr122->setProperty("DataDisplayName", QVariant(QCoreApplication::translate("ACR_E11_Form", "ACRCycCntr122", nullptr)));
        DD_Activation_Status->setProperty("DataDisplayName", QVariant(QCoreApplication::translate("ACR_E11_Form", "Activation_Status", nullptr)));
        groupBox_2->setTitle(QCoreApplication::translate("ACR_E11_Form", "\350\275\257\344\273\266\347\211\210\346\234\254", nullptr));
        DD_BSW->setProperty("DataDisplayName", QVariant(QCoreApplication::translate("ACR_E11_Form", "BSW", nullptr)));
        DD_BSW->setProperty("DataDisplay", QVariant(QCoreApplication::translate("ACR_E11_Form", "---", nullptr)));
        DD_SV->setProperty("DataDisplayName", QVariant(QCoreApplication::translate("ACR_E11_Form", "SV   ", nullptr)));
        DD_SV->setProperty("DataDisplay", QVariant(QCoreApplication::translate("ACR_E11_Form", "---", nullptr)));
        DD_FBL->setProperty("DataDisplayName", QVariant(QCoreApplication::translate("ACR_E11_Form", "FBL  ", nullptr)));
        DD_FBL->setProperty("DataDisplay", QVariant(QCoreApplication::translate("ACR_E11_Form", "---", nullptr)));
        groupBox_4->setTitle(QCoreApplication::translate("ACR_E11_Form", "ACR_121", nullptr));
        label_11->setText(QCoreApplication::translate("ACR_E11_Form", "ACR_Req_LH", nullptr));
        CB_ACR_Req_LH->setItemText(0, QCoreApplication::translate("ACR_E11_Form", "No Request", nullptr));
        CB_ACR_Req_LH->setItemText(1, QCoreApplication::translate("ACR_E11_Form", "Belt Park", nullptr));
        CB_ACR_Req_LH->setItemText(2, QCoreApplication::translate("ACR_E11_Form", "Belt Slack Remove", nullptr));
        CB_ACR_Req_LH->setItemText(3, QCoreApplication::translate("ACR_E11_Form", "Haptic Warning Level 1", nullptr));
        CB_ACR_Req_LH->setItemText(4, QCoreApplication::translate("ACR_E11_Form", "Haptic Warning Level 2", nullptr));
        CB_ACR_Req_LH->setItemText(5, QCoreApplication::translate("ACR_E11_Form", "Haptic Warning Level 3", nullptr));
        CB_ACR_Req_LH->setItemText(6, QCoreApplication::translate("ACR_E11_Form", "Retract Activation Level 1", nullptr));
        CB_ACR_Req_LH->setItemText(7, QCoreApplication::translate("ACR_E11_Form", "Retract Activation Level 2", nullptr));
        CB_ACR_Req_LH->setItemText(8, QCoreApplication::translate("ACR_E11_Form", "Retract Activation Level 3", nullptr));
        CB_ACR_Req_LH->setItemText(9, QCoreApplication::translate("ACR_E11_Form", "Retract Activation Level 4", nullptr));
        CB_ACR_Req_LH->setItemText(10, QCoreApplication::translate("ACR_E11_Form", "Retract Activation Level 5", nullptr));
        CB_ACR_Req_LH->setItemText(11, QCoreApplication::translate("ACR_E11_Form", "Retract Activation Level 6", nullptr));
        CB_ACR_Req_LH->setItemText(12, QCoreApplication::translate("ACR_E11_Form", "Retract Activation Level 7", nullptr));

        groupBox_5->setTitle(QCoreApplication::translate("ACR_E11_Form", "ACR_Probe", nullptr));
        DD_HSPD_Phy->setProperty("DataDisplayName", QVariant(QCoreApplication::translate("ACR_E11_Form", "HSPD", nullptr)));
        DD_CANW_Phy->setProperty("DataDisplayName", QVariant(QCoreApplication::translate("ACR_E11_Form", "CANW", nullptr)));
        DD_VHBH_Phy->setProperty("DataDisplayName", QVariant(QCoreApplication::translate("ACR_E11_Form", "VHBH", nullptr)));
        DD_TEM_Phy->setProperty("DataDisplayName", QVariant(QCoreApplication::translate("ACR_E11_Form", "TEM", nullptr)));
        DD_VHBL_Phy->setProperty("DataDisplayName", QVariant(QCoreApplication::translate("ACR_E11_Form", "VHBL", nullptr)));
        DD_VCC_Phy->setProperty("DataDisplayName", QVariant(QCoreApplication::translate("ACR_E11_Form", "VCC", nullptr)));
        DD_VBAT_Phy->setProperty("DataDisplayName", QVariant(QCoreApplication::translate("ACR_E11_Form", "VBAT", nullptr)));
        DD_CUR_Phy->setProperty("DataDisplayName", QVariant(QCoreApplication::translate("ACR_E11_Form", "CUR", nullptr)));
    } // retranslateUi

};

namespace Ui {
    class ACR_E11_Form: public Ui_ACR_E11_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACR_E11_FORM_H

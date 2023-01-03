/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_E11;
    QAction *LoadVariables;
    QAction *LoadDBC;
    QAction *action_H53;
    QAction *Automation;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QFormLayout *formLayout;
    QLabel *label;
    QComboBox *DeviceNameComboBox;
    QLabel *label_2;
    QComboBox *DeviceIDCamboBox;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QComboBox *ABitComboBox;
    QLabel *label_5;
    QComboBox *ChannelIDComboBox;
    QComboBox *DBitComboBox;
    QLabel *label_3;
    QLabel *label_6;
    QComboBox *WorkingModeComboBox;
    QLabel *label_4;
    QLabel *label_7;
    QComboBox *ResistanceComboBox;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_7;
    QPushButton *OpenDevice;
    QPushButton *InitCAN;
    QPushButton *OpenCAN;
    QPushButton *Reset;
    QPushButton *CloseDevice;
    QSpacerItem *verticalSpacer_2;
    QGroupBox *TableContainer;
    QGridLayout *gridLayout_4;
    QHBoxLayout *TableFunContainer;
    QCheckBox *EnableScroll;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_2;
    QFrame *horizontalFrame;
    QHBoxLayout *horizontalLayout;
    QLabel *label_8;
    QLineEdit *DataID;
    QLabel *label_11;
    QLineEdit *DLCEdit;
    QLabel *label_10;
    QComboBox *MessageFrameTypeComboBox;
    QLabel *label_9;
    QComboBox *MessageTransmitComboBox;
    QGridLayout *DataContainer;
    QGridLayout *gridLayout;
    QPushButton *Send;
    QPushButton *ConfigAutoSend;
    QPushButton *AutoSend;
    QCheckBox *SaveLog;
    QSpacerItem *horizontalSpacer;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_Tools;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(748, 554);
        action_E11 = new QAction(MainWindow);
        action_E11->setObjectName("action_E11");
        LoadVariables = new QAction(MainWindow);
        LoadVariables->setObjectName("LoadVariables");
        LoadDBC = new QAction(MainWindow);
        LoadDBC->setObjectName("LoadDBC");
        action_H53 = new QAction(MainWindow);
        action_H53->setObjectName("action_H53");
        Automation = new QAction(MainWindow);
        Automation->setObjectName("Automation");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_3 = new QVBoxLayout(centralwidget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName("gridLayout_3");
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(-1, -1, -1, 0);
        groupBox_5 = new QGroupBox(centralwidget);
        groupBox_5->setObjectName("groupBox_5");
        verticalLayout = new QVBoxLayout(groupBox_5);
        verticalLayout->setObjectName("verticalLayout");
        groupBox = new QGroupBox(groupBox_5);
        groupBox->setObjectName("groupBox");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        formLayout = new QFormLayout(groupBox);
        formLayout->setObjectName("formLayout");
        label = new QLabel(groupBox);
        label->setObjectName("label");
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMaximumSize(QSize(55, 16777215));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        DeviceNameComboBox = new QComboBox(groupBox);
        DeviceNameComboBox->setObjectName("DeviceNameComboBox");

        formLayout->setWidget(0, QFormLayout::FieldRole, DeviceNameComboBox);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setMaximumSize(QSize(55, 16777215));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        DeviceIDCamboBox = new QComboBox(groupBox);
        DeviceIDCamboBox->addItem(QString());
        DeviceIDCamboBox->setObjectName("DeviceIDCamboBox");

        formLayout->setWidget(1, QFormLayout::FieldRole, DeviceIDCamboBox);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(groupBox_5);
        groupBox_2->setObjectName("groupBox_2");
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName("gridLayout_2");
        ABitComboBox = new QComboBox(groupBox_2);
        ABitComboBox->setObjectName("ABitComboBox");

        gridLayout_2->addWidget(ABitComboBox, 3, 1, 1, 1);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName("label_5");
        sizePolicy1.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(label_5, 3, 0, 1, 1);

        ChannelIDComboBox = new QComboBox(groupBox_2);
        ChannelIDComboBox->addItem(QString());
        ChannelIDComboBox->addItem(QString());
        ChannelIDComboBox->setObjectName("ChannelIDComboBox");

        gridLayout_2->addWidget(ChannelIDComboBox, 0, 1, 1, 1);

        DBitComboBox = new QComboBox(groupBox_2);
        DBitComboBox->setObjectName("DBitComboBox");

        gridLayout_2->addWidget(DBitComboBox, 4, 1, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName("label_3");

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName("label_6");

        gridLayout_2->addWidget(label_6, 4, 0, 1, 1);

        WorkingModeComboBox = new QComboBox(groupBox_2);
        WorkingModeComboBox->setObjectName("WorkingModeComboBox");

        gridLayout_2->addWidget(WorkingModeComboBox, 2, 1, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName("label_4");

        gridLayout_2->addWidget(label_4, 2, 0, 1, 1);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName("label_7");

        gridLayout_2->addWidget(label_7, 5, 0, 1, 1);

        ResistanceComboBox = new QComboBox(groupBox_2);
        ResistanceComboBox->setObjectName("ResistanceComboBox");

        gridLayout_2->addWidget(ResistanceComboBox, 5, 1, 1, 1);


        verticalLayout->addWidget(groupBox_2);

        groupBox_6 = new QGroupBox(groupBox_5);
        groupBox_6->setObjectName("groupBox_6");
        gridLayout_7 = new QGridLayout(groupBox_6);
        gridLayout_7->setObjectName("gridLayout_7");
        OpenDevice = new QPushButton(groupBox_6);
        OpenDevice->setObjectName("OpenDevice");
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(OpenDevice->sizePolicy().hasHeightForWidth());
        OpenDevice->setSizePolicy(sizePolicy2);
        OpenDevice->setAutoDefault(false);

        gridLayout_7->addWidget(OpenDevice, 0, 0, 1, 1);

        InitCAN = new QPushButton(groupBox_6);
        InitCAN->setObjectName("InitCAN");
        sizePolicy2.setHeightForWidth(InitCAN->sizePolicy().hasHeightForWidth());
        InitCAN->setSizePolicy(sizePolicy2);

        gridLayout_7->addWidget(InitCAN, 0, 1, 1, 1);

        OpenCAN = new QPushButton(groupBox_6);
        OpenCAN->setObjectName("OpenCAN");
        sizePolicy2.setHeightForWidth(OpenCAN->sizePolicy().hasHeightForWidth());
        OpenCAN->setSizePolicy(sizePolicy2);

        gridLayout_7->addWidget(OpenCAN, 1, 0, 1, 1);

        Reset = new QPushButton(groupBox_6);
        Reset->setObjectName("Reset");
        sizePolicy2.setHeightForWidth(Reset->sizePolicy().hasHeightForWidth());
        Reset->setSizePolicy(sizePolicy2);

        gridLayout_7->addWidget(Reset, 2, 0, 1, 1);

        CloseDevice = new QPushButton(groupBox_6);
        CloseDevice->setObjectName("CloseDevice");
        sizePolicy2.setHeightForWidth(CloseDevice->sizePolicy().hasHeightForWidth());
        CloseDevice->setSizePolicy(sizePolicy2);

        gridLayout_7->addWidget(CloseDevice, 2, 1, 1, 1);


        verticalLayout->addWidget(groupBox_6);


        verticalLayout_4->addWidget(groupBox_5);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_2);


        gridLayout_3->addLayout(verticalLayout_4, 0, 0, 1, 1);

        TableContainer = new QGroupBox(centralwidget);
        TableContainer->setObjectName("TableContainer");
        gridLayout_4 = new QGridLayout(TableContainer);
        gridLayout_4->setObjectName("gridLayout_4");
        gridLayout_4->setContentsMargins(-1, 0, -1, -1);
        TableFunContainer = new QHBoxLayout();
        TableFunContainer->setObjectName("TableFunContainer");
        TableFunContainer->setContentsMargins(-1, 0, -1, -1);
        EnableScroll = new QCheckBox(TableContainer);
        EnableScroll->setObjectName("EnableScroll");
        sizePolicy2.setHeightForWidth(EnableScroll->sizePolicy().hasHeightForWidth());
        EnableScroll->setSizePolicy(sizePolicy2);
        EnableScroll->setChecked(true);

        TableFunContainer->addWidget(EnableScroll);

        comboBox = new QComboBox(TableContainer);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");

        TableFunContainer->addWidget(comboBox);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        TableFunContainer->addItem(horizontalSpacer_2);


        gridLayout_4->addLayout(TableFunContainer, 0, 0, 1, 1);


        gridLayout_3->addWidget(TableContainer, 0, 1, 1, 1);


        verticalLayout_3->addLayout(gridLayout_3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(-1, -1, -1, 0);
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName("groupBox_3");
        sizePolicy2.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy2);
        verticalLayout_2 = new QVBoxLayout(groupBox_3);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(-1, 0, -1, 0);
        horizontalFrame = new QFrame(groupBox_3);
        horizontalFrame->setObjectName("horizontalFrame");
        sizePolicy2.setHeightForWidth(horizontalFrame->sizePolicy().hasHeightForWidth());
        horizontalFrame->setSizePolicy(sizePolicy2);
        horizontalLayout = new QHBoxLayout(horizontalFrame);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(-1, 0, -1, 0);
        label_8 = new QLabel(horizontalFrame);
        label_8->setObjectName("label_8");
        sizePolicy2.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy2);
        label_8->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_8);

        DataID = new QLineEdit(horizontalFrame);
        DataID->setObjectName("DataID");
        sizePolicy2.setHeightForWidth(DataID->sizePolicy().hasHeightForWidth());
        DataID->setSizePolicy(sizePolicy2);
        DataID->setMaximumSize(QSize(30, 16777215));
        DataID->setMaxLength(3);
        DataID->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(DataID);

        label_11 = new QLabel(horizontalFrame);
        label_11->setObjectName("label_11");
        sizePolicy1.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(label_11);

        DLCEdit = new QLineEdit(horizontalFrame);
        DLCEdit->setObjectName("DLCEdit");
        sizePolicy2.setHeightForWidth(DLCEdit->sizePolicy().hasHeightForWidth());
        DLCEdit->setSizePolicy(sizePolicy2);
        DLCEdit->setMaximumSize(QSize(30, 16777215));
        DLCEdit->setLayoutDirection(Qt::LeftToRight);
        DLCEdit->setMaxLength(2);
        DLCEdit->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(DLCEdit);

        label_10 = new QLabel(horizontalFrame);
        label_10->setObjectName("label_10");
        sizePolicy2.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(label_10);

        MessageFrameTypeComboBox = new QComboBox(horizontalFrame);
        MessageFrameTypeComboBox->setObjectName("MessageFrameTypeComboBox");
        sizePolicy2.setHeightForWidth(MessageFrameTypeComboBox->sizePolicy().hasHeightForWidth());
        MessageFrameTypeComboBox->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(MessageFrameTypeComboBox);

        label_9 = new QLabel(horizontalFrame);
        label_9->setObjectName("label_9");
        sizePolicy1.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(label_9);

        MessageTransmitComboBox = new QComboBox(horizontalFrame);
        MessageTransmitComboBox->setObjectName("MessageTransmitComboBox");
        sizePolicy2.setHeightForWidth(MessageTransmitComboBox->sizePolicy().hasHeightForWidth());
        MessageTransmitComboBox->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(MessageTransmitComboBox);


        verticalLayout_2->addWidget(horizontalFrame);

        DataContainer = new QGridLayout();
        DataContainer->setObjectName("DataContainer");

        verticalLayout_2->addLayout(DataContainer);


        horizontalLayout_3->addWidget(groupBox_3);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, -1, -1);
        Send = new QPushButton(centralwidget);
        Send->setObjectName("Send");
        sizePolicy2.setHeightForWidth(Send->sizePolicy().hasHeightForWidth());
        Send->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(Send, 0, 0, 1, 1);

        ConfigAutoSend = new QPushButton(centralwidget);
        ConfigAutoSend->setObjectName("ConfigAutoSend");

        gridLayout->addWidget(ConfigAutoSend, 0, 1, 1, 1);

        AutoSend = new QPushButton(centralwidget);
        AutoSend->setObjectName("AutoSend");

        gridLayout->addWidget(AutoSend, 1, 0, 1, 1);

        SaveLog = new QCheckBox(centralwidget);
        SaveLog->setObjectName("SaveLog");

        gridLayout->addWidget(SaveLog, 1, 1, 1, 1);


        horizontalLayout_3->addLayout(gridLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout_3);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 748, 22));
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        menu_Tools = new QMenu(menubar);
        menu_Tools->setObjectName("menu_Tools");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_Tools->menuAction());
        menu->addAction(action_E11);
        menu->addAction(action_H53);
        menu_Tools->addAction(LoadVariables);
        menu_Tools->addAction(LoadDBC);
        menu_Tools->addAction(Automation);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        action_E11->setText(QCoreApplication::translate("MainWindow", "ACR(E11)", nullptr));
        LoadVariables->setText(QCoreApplication::translate("MainWindow", "\345\212\240\350\275\275\345\217\230\351\207\217", nullptr));
        LoadDBC->setText(QCoreApplication::translate("MainWindow", "\345\212\240\350\275\275DBC", nullptr));
        action_H53->setText(QCoreApplication::translate("MainWindow", "ACR(H53)", nullptr));
        Automation->setText(QCoreApplication::translate("MainWindow", "\350\207\252\345\212\250\345\214\226", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "\345\217\202\346\225\260\351\205\215\347\275\256", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\350\256\276\345\244\207\351\200\211\346\213\251", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\350\256\276\345\244\207\347\261\273\345\236\213", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\350\256\276\345\244\207\347\264\242\345\274\225", nullptr));
        DeviceIDCamboBox->setItemText(0, QCoreApplication::translate("MainWindow", "0", nullptr));

        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\351\200\232\351\201\223\351\205\215\347\275\256", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\344\273\262\350\243\201\345\237\237\346\263\242\347\211\271\347\216\207", nullptr));
        ChannelIDComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "0", nullptr));
        ChannelIDComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "1", nullptr));

        label_3->setText(QCoreApplication::translate("MainWindow", "CAN\351\200\232\351\201\223", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\345\237\237\346\263\242\347\211\271\347\216\207", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\345\267\245\344\275\234\346\250\241\345\274\217", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\347\273\210\347\253\257\347\224\265\351\230\273", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("MainWindow", "\350\256\276\345\244\207\346\223\215\344\275\234", nullptr));
        OpenDevice->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\350\256\276\345\244\207", nullptr));
        InitCAN->setText(QCoreApplication::translate("MainWindow", "\345\210\235\345\247\213\345\214\226CAN", nullptr));
        OpenCAN->setText(QCoreApplication::translate("MainWindow", "\345\220\257\345\212\250CAN", nullptr));
        Reset->setText(QCoreApplication::translate("MainWindow", "\345\244\215\344\275\215", nullptr));
        CloseDevice->setText(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255\350\256\276\345\244\207", nullptr));
        TableContainer->setTitle(QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\346\216\245\346\224\266", nullptr));
        EnableScroll->setText(QCoreApplication::translate("MainWindow", "\346\273\232\345\212\250", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Trace", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Toggle Time Mode", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "Diage Trace", nullptr));

        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\345\217\221\351\200\201", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "ID(0x):", nullptr));
        DataID->setText(QString());
        DataID->setPlaceholderText(QCoreApplication::translate("MainWindow", "001", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "DLC:", nullptr));
        DLCEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "8", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "\345\215\217\350\256\256\357\274\232", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201\346\226\271\345\274\217\357\274\232", nullptr));
        Send->setText(QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\345\217\221\351\200\201", nullptr));
        ConfigAutoSend->setText(QCoreApplication::translate("MainWindow", "\351\205\215\347\275\256\350\207\252\345\212\250\345\217\221\351\200\201", nullptr));
        AutoSend->setText(QCoreApplication::translate("MainWindow", "\345\256\232\346\227\266\345\217\221\351\200\201", nullptr));
        SaveLog->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230Log", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\351\235\242\346\235\277(Panel)", nullptr));
        menu_Tools->setTitle(QCoreApplication::translate("MainWindow", "\345\267\245\345\205\267(Tool)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

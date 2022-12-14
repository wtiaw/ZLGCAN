QT       += core gui
QT       += concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

CONFIG += c++17
CONFIG += console


msvc {
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Automation/AutomationNode.cpp \
    Automation/AutomationNode_Loop.cpp \
    Automation/AutomationSystem.cpp \
    CustomThread/PerformanceFrequency.cpp \
    CustomThread/QReceiveItem.cpp \
    CustomThread/QReceiveThread.cpp \
    CustomThread/QThreadBase.cpp \
    CustomWidget/CheckBox/QDrawerCheckBox.cpp \
    CustomWidget/DataEdit.cpp \
    CustomWidget/Frame/QStackedWidget.cpp \
    CustomWidget/LineEdit/UnitQLineEdit.cpp \
    CustomWidget/TableWidget/QMessageTableWidget.cpp \
    CustomWidget/ToolBox.cpp \
    CustomWidget/ToolPage.cpp \
    Library/QCANLibrary.cpp \
    Library/QWidgetLibrary.cpp \
    Setting/QAutoMessageConfig.cpp \
    Setting/QDeviceSettingConfig.cpp \
    Setting/QSettingConfigBase.cpp \
    Setting/QSystemVariables.cpp \
    Windows/AutoSendConfigWindow.cpp \
    Windows/AutomationWindow.cpp \
    Windows/LoadDBCWindow.cpp \
    Windows/LoadVariablesWindow.cpp \
    Windows/Pannel/FormBase.cpp \
    Windows/Pannel/ACR_E11_Form.cpp \
    Windows/Pannel/ACR_H53_Form.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Automation/AutomationNode.h \
    Automation/AutomationNode_Loop.h \
    Automation/AutomationSystem.h \
    CustomThread/PerformanceFrequency.h \
    CustomThread/QReceiveItem.h \
    CustomThread/QReceiveThread.h \
    CustomThread/QThreadBase.h \
    CustomWidget/CheckBox/QDrawerCheckBox.h \
    CustomWidget/DataEdit.h \
    CustomWidget/Frame/QStackedWidget.h \
    CustomWidget/LineEdit/UnitQLineEdit.h \
    CustomWidget/TableWidget/QMessageTableWidget.h \
    CustomWidget/ToolBox.h \
    CustomWidget/ToolPage.h \
    Data/CustomEnum.h \
    Data/FromeStruct.h \
    Data/VariableStruct.h \
    Library/QCANLibrary.h \
    Library/QWidgetLibrary.h \
    Library/CircinalQueue.h \
    Setting/QAutoMessageConfig.h \
    Setting/QDeviceSettingConfig.h \
    Setting/QSettingConfigBase.h \
    Setting/QSystemVariables.h \
    Windows/AutoSendConfigWindow.h \
    Windows/AutomationWindow.h \
    Windows/LoadDBCWindow.h \
    Windows/LoadVariablesWindow.h \
    Windows/Pannel/FormBase.h \
    Windows/Pannel/ACR_E11_Form.h \
    Windows/Pannel/ACR_H53_Form.h \
    mainwindow.h

FORMS += \
    CustomWidget/Frame/QStackedWidget.ui \
    CustomWidget/ToolBox.ui \
    CustomWidget/ToolPage.ui \
    Windows/AutoSendConfigWindow.ui \
    Windows/AutomationWindow.ui \
    Windows/LoadDBCWindow.ui \
    Windows/LoadVariablesWindow.ui \
    Windows/Pannel/ACR_E11_Form.ui \
    Windows/Pannel/ACR_H53_Form.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RESOURCES += \
    Icon.qrc

win32: LIBS += -L$$PWD/include/bl_x64/ -lbinlog

INCLUDEPATH += $$PWD/include/bl_x64
DEPENDPATH += $$PWD/include/bl_x64

win32: LIBS += -L$$PWD/include/DataDisplayWidget/ -lDataDisplayWidgetPlugin

INCLUDEPATH += $$PWD/include/DataDisplayWidget
DEPENDPATH += $$PWD/include/DataDisplayWidget

win32: LIBS += -L$$PWD/include/zlgcan_x64/ -lzlgcan

INCLUDEPATH += $$PWD/include/zlgcan_x64
DEPENDPATH += $$PWD/include/zlgcan_x64

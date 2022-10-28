QT       += core gui
QT       += concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CustomThread/PerformanceFrequency.cpp \
    CustomThread/QReceiveItem.cpp \
    CustomThread/QReceiveThread.cpp \
    CustomThread/QThreadBase.cpp \
    CustomThread/QTransmitThread.cpp \
    CustomWidget/CheckBox/QDrawerCheckBox.cpp \
    CustomWidget/DataEdit.cpp \
    CustomWidget/Frame/QStackedWidget.cpp \
    CustomWidget/TableWidget/QMessageTableWidget.cpp \
    CustomWidget/ToolBox.cpp \
    CustomWidget/ToolPage.cpp \
    Library/QCANLibrary.cpp \
    Library/QWidgetLibrary.cpp \
    Setting/QAutoMessageConfig.cpp \
    Setting/QDeviceSettingConfig.cpp \
    Setting/QSettingConfigBase.cpp \
    Windows/ACRForm.cpp \
    Windows/AutoSendConfigWindow.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    CustomThread/PerformanceFrequency.h \
    CustomThread/QReceiveItem.h \
    CustomThread/QReceiveThread.h \
    CustomThread/QThreadBase.h \
    CustomThread/QTransmitThread.h \
    CustomWidget/CheckBox/QDrawerCheckBox.h \
    CustomWidget/DataEdit.h \
    CustomWidget/Frame/QStackedWidget.h \
    CustomWidget/TableWidget/QMessageTableWidget.h \
    CustomWidget/ToolBox.h \
    CustomWidget/ToolPage.h \
    Data/FromeStruct.h \
    Library/QCANLibrary.h \
    Library/QWidgetLibrary.h \
    Setting/QAutoMessageConfig.h \
    Setting/QDeviceSettingConfig.h \
    Setting/QSettingConfigBase.h \
    Windows/ACRForm.h \
    Windows/AutoSendConfigWindow.h \
    mainwindow.h

FORMS += \
    CustomWidget/Frame/QStackedWidget.ui \
    CustomWidget/ToolBox.ui \
    CustomWidget/ToolPage.ui \
    Windows/ACRForm.ui \
    Windows/AutoSendConfigWindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix|win32: LIBS += -L$$PWD/zlgcan_x64/ -lzlgcan

INCLUDEPATH += $$PWD/zlgcan_x64
DEPENDPATH += $$PWD/zlgcan_x64

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/zlgcan_x64/zlgcan.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/zlgcan_x64/libzlgcan.a

RESOURCES += \
    Icon.qrc

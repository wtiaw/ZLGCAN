QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CustomWidget/DataEdit.cpp \
    ReceiveDataThread.cpp \
    Setting/settingconfig.cpp \
    Windows/AutoSendConfigWindow.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    CustomWidget/DataEdit.h \
    ReceiveDataThread.h \
    Setting/settingconfig.h \
    Windows/AutoSendConfigWindow.h \
    mainwindow.h

FORMS += \
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

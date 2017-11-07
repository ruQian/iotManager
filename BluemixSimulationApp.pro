#-------------------------------------------------
#
# Project created by QtCreator 2017-11-03T10:53:43
#
#-------------------------------------------------

QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = BluemixSimulationApp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    settingdialog.cpp \
    adddevtdialog.cpp \
    adddevtsigdlg.cpp \
    adddevicedialog.cpp \
    adddevicesdialog.cpp \
    customtreewidget.cpp \
    iotsimulation.cpp \
    qiotdevthread.cpp

HEADERS  += mainwindow.h \
    settingdialog.h \
    adddevtdialog.h \
    adddevtsigdlg.h \
    types.h \
    adddevicedialog.h \
    adddevicesdialog.h \
    customtreewidget.h \
    iotsimulation.h \
    qiotdevthread.h

FORMS    += mainwindow.ui \
    settingdialog.ui \
    adddevtdialog.ui \
    adddevtsigdlg.ui \
    adddevicedialog.ui \
    adddevicesdialog.ui




win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lqmqtt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lqmqttd

INCLUDEPATH += $$PWD/mqtt
DEPENDPATH += $$PWD/include




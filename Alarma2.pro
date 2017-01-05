#-------------------------------------------------
#
# Project created by QtCreator 2016-12-25T23:51:46
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Alarma2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    options.cpp \
    dialogsure.cpp \
    systemtray.cpp \
    settings.cpp \
    alarmsconfigdialog.cpp \
    alarmsettings.cpp \
    alarm.cpp

HEADERS  += mainwindow.h \
    options.h \
    dialogsure.h \
    systemtray.h \
    settings.h \
    alarmsconfigdialog.h \
    alarmsettings.h \
    alarm.h

FORMS    += mainwindow.ui \
    options.ui \
    dialogsure.ui \
    alarmsconfigdialog.ui

DISTFILES +=

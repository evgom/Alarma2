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
    alarms.cpp \
    dialogsure.cpp \
    systemtray.cpp \
    settings.cpp

HEADERS  += mainwindow.h \
    options.h \
    alarms.h \
    dialogsure.h \
    systemtray.h \
    settings.h

FORMS    += mainwindow.ui \
    options.ui \
    alarms.ui \
    dialogsure.ui

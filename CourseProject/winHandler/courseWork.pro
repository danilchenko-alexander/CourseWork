#-------------------------------------------------
#
# Project created by QtCreator 2016-05-17T19:23:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = courseWork
TEMPLATE = app
LIBS+= C:\Windows\System32\PowrProf.dll

SOURCES += main.cpp\
        mainwindow.cpp \
    slider.cpp \
    WHandler.cpp \
    keyboard.cpp \
    powerState.cpp

HEADERS  += mainwindow.h \
    slider.h \
    WHandler.h \
    libraries.h \
    keyboard.h \
    powerState.h

FORMS    += mainwindow.ui

DEFINES *= _AFXDLL_MBCS

RESOURCES += \
    resources.qrc

#-------------------------------------------------
#
# Project created by QtCreator 2018-05-12T11:25:51
#
#-------------------------------------------------

QT       += core gui
QT += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WaveInterference
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    point.cpp \
    model.cpp \
    matrix.cpp \
    vector4.cpp \
    transformations.cpp \
    customdialog.cpp

HEADERS += \
        mainwindow.h \
    point.h \
    model.h \
    matrix.h \
    vector4.h \
    transformations.h \
    customdialog.h

FORMS += \
        mainwindow.ui

#-------------------------------------------------
#
# Project created by QtCreator 2014-10-05T12:39:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app


SOURCES += main.cpp\
        loginwindow.cpp \
    network.cpp \
    controller.cpp \
    encoder.cpp \
    friendwindow.cpp

HEADERS  += loginwindow.h \
    network.h \
    controller.h \
    encoder.h \
    friendwindow.h

FORMS    += loginwindow.ui \
    friendwindow.ui

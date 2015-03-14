#-------------------------------------------------
#
# Project created by QtCreator 2014-10-05T19:23:53
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server
TEMPLATE = app
LIBS += -L/usr/lib -lssl -lcrypto -lcryptopp
CONFIG += c++11

SOURCES += main.cpp\
        monitoringwindow.cpp \
    database.cpp \
    encoder.cpp \
    controller.cpp \
    requesthandler.cpp \
    connection.cpp

HEADERS  += monitoringwindow.h \
    database.h \
    encoder.h \
    controller.h \
    requesthandler.h \
    connection.h

FORMS    += monitoringwindow.ui

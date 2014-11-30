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


SOURCES += main.cpp\
        monitoringwindow.cpp \
    database.cpp \
    encoder.cpp \
    connection.cpp \
    controller.cpp \
    requesthandler.cpp

HEADERS  += monitoringwindow.h \
    database.h \
    encoder.h \
    connection.h \
    controller.h \
    requesthandler.h

FORMS    += monitoringwindow.ui

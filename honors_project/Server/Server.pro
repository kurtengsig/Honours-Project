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
    network.cpp \
    database.cpp \
    encoder.cpp

HEADERS  += monitoringwindow.h \
    network.h \
    database.h \
    encoder.h

FORMS    += monitoringwindow.ui

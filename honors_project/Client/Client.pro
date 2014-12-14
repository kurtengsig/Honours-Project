#-------------------------------------------------
#
# Project created by QtCreator 2014-10-05T12:39:42
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app
LIBS += -L/usr/lib -lssl -lcrypto
CONFIG += c++11

SOURCES += main.cpp\
        loginwindow.cpp \
    controller.cpp \
    encoder.cpp \
    friendwindow.cpp \
    addfrienddialog.cpp \
    conversationwindow.cpp \
    conversationcontroller.cpp \
    serverconnection.cpp \
    registerdialog.cpp \
    peerconnectionlistener.cpp \
    peerconnectionsender.cpp

HEADERS  += loginwindow.h \
    controller.h \
    encoder.h \
    friendwindow.h \
    addfrienddialog.h \
    conversationwindow.h \
    conversationcontroller.h \
    serverconnection.h \
    registerdialog.h \
    peerconnectionlistener.h \
    peerconnectionsender.h

FORMS    += loginwindow.ui \
    friendwindow.ui \
    addfrienddialog.ui \
    conversationwindow.ui \
    registerdialog.ui

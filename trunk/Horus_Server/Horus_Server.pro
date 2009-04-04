# -------------------------------------------------
# Project created by QtCreator 2009-03-28T21:10:31
# -------------------------------------------------
QT += network \
    sql
QT -= gui
TARGET = Horus_Server
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += main.cpp \
    client.cpp \
    fortuneserver.cpp \
    fortunethread.cpp
HEADERS += module.h \
    client.h \
    fortuneserver.h \
    fortunethread.h \
    ../Common/Defines.h \
    ../Common/ModuleContainer.h \
    ../Common/Defines.h \
    ../Common/CommunicationContainer.h \
    ../Common/LoginContainer.h \
    ../Common/ConnexionMessage.h

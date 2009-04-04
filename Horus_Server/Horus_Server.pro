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
    Client.cpp \
    Server.cpp \
    Thread.cpp \
    Sql.cpp
HEADERS += module.h \
    Client.h \
    Server.h \
    Thread.h \
    Sql.h \
    ../Common/Defines.h \
    ../Common/ModuleContainer.h \
    ../Common/Defines.h \
    ../Common/CommunicationContainer.h \
    ../Common/LoginContainer.h \
    ../Common/ConnexionMessage.h

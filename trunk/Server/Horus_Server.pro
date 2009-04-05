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
    ClientSocket.cpp \
    Server.cpp \
    Sql.cpp \
    ../Common/CommLogin.cpp \
    Settings.cpp
HEADERS += Module.h \
    ClientSocket.h \
    Server.h \
    Sql.h \
    ../Common/Defines.h \
    ../Common/CommInit.h \
    ../Common/CommLogin.h \
    ../Common/CommModule.h \
    ../Common/CommRequest.h \
    Settings.h

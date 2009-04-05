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
    Settings.cpp \
    Login.cpp \
    Request.cpp \
    ../Common/CommMiniString.cpp \
    ../Common/CommLogin.cpp \
    ../Common/CommInit.cpp \
    ../Common/CommModule.cpp \
    ../Common/CommRequest.cpp
HEADERS += Module.h \
    ClientSocket.h \
    Server.h \
    Sql.h \
    Settings.h \
    Login.h \
    Request.h \
    ../Common/CommRequest.h \
    ../Common/CommModule.h \
    ../Common/CommMiniString.h \
    ../Common/CommLogin.h \
    ../Common/CommInit.h \
    ../Common/Defines.h

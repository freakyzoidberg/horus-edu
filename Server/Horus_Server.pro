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
    ThreadPacket.cpp \
    PluginManager.cpp \
    ../Common/CommLogin.cpp \
    ../Common/CommInit.cpp \
    ../Common/CommModule.cpp \
    ../Common/CommPacket.cpp \
    ../Common/CommError.cpp \
    User.cpp \
    ../Common/CommSocket.cpp \
    InterfaceServer.cpp
HEADERS += Module.h \
    ClientSocket.h \
    Server.h \
    Sql.h \
    Settings.h \
    ThreadPacket.h \
    PluginManager.h \
    ../Common/CommPacket.h \
    ../Common/CommModule.h \
    ../Common/CommLogin.h \
    ../Common/CommInit.h \
    ../Common/Defines.h \
    ../Common/CommError.h \
    User.h \
    ../Common/CommSocket.h \
    ../Common/ModulePacket.h \
    InterfaceServer.h \
    Plugins/IServerPlugin.h \
    Plugins/IServer.h

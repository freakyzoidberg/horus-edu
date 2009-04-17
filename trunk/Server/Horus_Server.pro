# -------------------------------------------------
# Project created by QtCreator 2009-03-28T21:10:31
# -------------------------------------------------
QT -= gui
QT += network sql
TARGET = Horus_Server
CONFIG -= app_bundle
CONFIG += console
TEMPLATE = app
SOURCES = \
    main.cpp \
    Sql.cpp \
    User.cpp \
    Server.cpp \
    Settings.cpp \
    ClientSocket.cpp \
    ThreadPacket.cpp \
    PluginManager.cpp \
    InterfaceServer.cpp \
    ../Common/CommInit.cpp \
    ../Common/CommError.cpp \
    ../Common/CommLogin.cpp \
    ../Common/CommModule.cpp \
    ../Common/CommPacket.cpp \
    ../Common/CommSocket.cpp
HEADERS = \
    Sql.h \
    User.h \
    Server.h \
    Settings.h \
    ClientSocket.h \
    ThreadPacket.h \
    PluginManager.h \
    InterfaceServer.h \
    Plugins/IServer.h \
    Plugins/IServerPlugin.h \
    ../Common/Defines.h \
    ../Common/CommInit.h \
    ../Common/CommError.h \
    ../Common/CommLogin.h \
    ../Common/CommModule.h \
    ../Common/CommPacket.h \
    ../Common/CommSocket.h \
    ../Common/ModulePacket.h

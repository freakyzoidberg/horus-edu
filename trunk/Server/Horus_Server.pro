# -------------------------------------------------
# Project created by QtCreator 2009-03-28T21:10:31
# -------------------------------------------------
QT -= gui
QT += network \
    sql
TARGET = Horus_Server
DEFINES += HORUS_SERVER
CONFIG -= app_bundle
CONFIG += console
TEMPLATE = app
SOURCES = main.cpp \
    Sql.cpp \
    Server.cpp \
    Settings.cpp \
    ClientSocket.cpp \
    UserSettings.cpp \
    Tree.cpp \
    ThreadPacket.cpp \
    PluginManager.cpp \
    ../Common/CommInit.cpp \
    ../Common/CommError.cpp \
    ../Common/CommLogin.cpp \
    ../Common/CommPlugin.cpp \
    ../Common/CommPacket.cpp \
    ../Common/CommSocket.cpp \
    ../Common/PluginPacket.cpp \
    Logs.cpp \
    ../Common/CommData.cpp \
    ../Common/Data.cpp \
    DataPlugin.cpp
HEADERS = Sql.h \
    Server.h \
    Settings.h \
    ClientSocket.h \
    ThreadPacket.h \
    UserSettings.h \
    Tree.h \
    ../Common/PluginManager.h \
    ../Common/Defines.h \
    ../Common/CommInit.h \
    ../Common/CommError.h \
    ../Common/CommLogin.h \
    ../Common/CommPlugin.h \
    ../Common/CommPacket.h \
    ../Common/CommSocket.h \
    ../Common/PLuginPacket.h \
    Logs.h \
    ../Common/Data.h \
    ../Common/CommData.h \
    ../Common/MetaPlugin.h \
    ../Common/Plugin.h \
    ../Common/DataPlugin.h \
    ../Common/UserData.h \
    ../Common/UserDataPlugin.h \
    ../Common/TreeData.h \
    ../Common/TreeDataPlugin.h \
    ../Common/NetworkPlugin.h

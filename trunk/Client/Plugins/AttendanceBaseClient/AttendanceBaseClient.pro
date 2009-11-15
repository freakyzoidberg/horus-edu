# -------------------------------------------------
# Project created by AbdErCreator 2009-04-09T19:51:57
# -------------------------------------------------
QT += sql
DEFINES += HORUS_CLIENT
TEMPLATE = lib
TARGET = AttendanceBaseClientMetaPlugin
HEADERS += ../../../Common/DataImplementations/AttendanceDataBase/AttendanceDataBasePlugin.h \
    ../../../Common/DataImplementations/AttendanceDataBase/AttendanceDataBase.h \
    ../../../Common/AttendanceDataPlugin.h \
    ../../../Common/AttendanceData.h \
    ../../../Common/UserDataPlugin.h \
    ../../../Common/UserData.h \
    ../../../Common/PluginManager.h \
    ../../../Common/Plugin.h \
    ../../../Common/MetaPlugin.h \
    ../../../Common/DataPlugin.h \
    ../../../Common/DataManager.h \
    ../../../Common/Data.h \
    ../../../Common/EventDataPlugin.h \
    ../../../Common/EventData.h
SOURCES += ../../../Common/DataImplementations/AttendanceDataBase/AttendanceDataBasePlugin.cpp \
    ../../../Common/DataImplementations/AttendanceDataBase/AttendanceDataBase.cpp

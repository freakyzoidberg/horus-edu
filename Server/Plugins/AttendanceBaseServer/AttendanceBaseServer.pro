# -------------------------------------------------
# Project created by someone
# -------------------------------------------------
QT += sql
DEFINES += HORUS_SERVER
TEMPLATE = lib
TARGET = AttendanceBaseServerMetaPlugin
HEADERS += AttendanceBaseServerMetaPlugin.h \
    ../../../Common/DataImplementations/AttendanceDataBase/AttendanceDataBasePlugin.h \
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
    ../../../Common/Data.h
SOURCES += ../../../Common/DataImplementations/AttendanceDataBase/AttendanceDataBasePlugin.cpp \
    ../../../Common/DataImplementations/AttendanceDataBase/AttendanceDataBase.cpp

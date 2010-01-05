# -------------------------------------------------
# Project created by someone
# -------------------------------------------------
QT += sql
DEFINES += HORUS_CLIENT
TEMPLATE = lib
TARGET = AttendanceBaseClientMetaPlugin
HEADERS += AttendanceBaseClientMetaPlugin.h \
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

TRANSLATIONS =	AttendanceBaseClientMetaPlugin_en.ts \
				AttendanceBaseClientMetaPlugin_fr.ts
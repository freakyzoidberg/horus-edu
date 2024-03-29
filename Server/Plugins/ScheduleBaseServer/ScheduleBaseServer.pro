# -------------------------------------------------
# Project created by someone
# -------------------------------------------------
QT += sql
DEFINES += HORUS_SERVER
TEMPLATE = lib
TARGET = ScheduleBaseServerMetaPlugin
HEADERS += ../../../Common/ScheduleDataPlugin.h \
    ../../../Common/ScheduleData.h \
    ../../../Common/DataImplementations/ScheduleDataBase/ScheduleDataBasePlugin.h \
    ../../../Common/DataImplementations/ScheduleDataBase/ScheduleDataBase.h \
    ../../../Common/PluginManager.h \
    ../../../Common/Plugin.h \
    ../../../Common/MetaPlugin.h \
    ../../../Common/DataPlugin.h \
    ../../../Common/DataManager.h \
    ../../../Common/Data.h \
    ScheduleBaseServerMetaPlugin.h \
    ../../../Common/TreeDataPlugin.h \
    ../../../Common/TreeData.h \
    ../../../Common/DataImplementations/ScheduleDataBase/ScheduleItem.h
SOURCES += ../../../Common/DataImplementations/ScheduleDataBase/ScheduleDataBasePlugin.cpp \
    ../../../Common/DataImplementations/ScheduleDataBase/ScheduleDataBase.cpp

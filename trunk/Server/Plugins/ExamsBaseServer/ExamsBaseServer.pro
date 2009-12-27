# -------------------------------------------------
# Project created by QtCreator 2009-04-09T19:51:57
# -------------------------------------------------
QT -= gui
QT += sql
CONFIG += qt debug
DEFINES += HORUS_SERVER
TEMPLATE = lib
TARGET = ExamsBaseServerMetaPlugin
SOURCES += \
	../../../Common/DataImplementations/ExamsDataBase/ExamsDataBase.cpp \
	../../../Common/DataImplementations/ExamsDataBase/ExamsDataBasePlugin.cpp
HEADERS += \
	../../../Common/DataImplementations/ExamsDataBase/ExamsDataBase.h \
	../../../Common/DataImplementations/ExamsDataBase/ExamsDataBasePlugin.h \
	../../../Common/ExamsData.h \
	../../../Common/ExamsDataPlugin.h \
	../../../Common/TreeData.h \
	../../../Common/TreeDataPlugin.h \
	../../../Common/MetaPlugin.h \
	../../../Common/Plugin.h \
	../../../Common/PluginManager.h \
	../../../Common/Data.h \
	../../../Common/DataPlugin.h \
	../../../Common/DataManager.h \
	ExamsBaseMetaPlugin.h

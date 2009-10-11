# -------------------------------------------------
# Project created by QtCreator 2009-04-09T19:51:57
# -------------------------------------------------
QT -= gui
QT += network \
    sql
DEFINES += HORUS_SERVER
TEMPLATE = lib
TARGET = FileBaseServerMetaPlugin
SOURCES += \
	../../../Common/DataImplementations/FileDataBase/FileDataBase.cpp \
    ../../../Common/DataImplementations/FileDataBase/FileDataBasePlugin.cpp \
	../../../Common/DataImplementations/FileDataBase/FileTransfert.cpp \
	FileServer.cpp \
	FileTransfertServer.cpp \
    FileNetworkPlugin.cpp
HEADERS += \
	../../../Common/DataImplementations/FileDataBase/FileDataBase.h \
    ../../../Common/DataImplementations/FileDataBase/FileDataBasePlugin.h \
	../../../Common/DataImplementations/FileDataBase/FileTransfert.h \
	../../../Common/Plugin.h \
    ../../../Common/PluginManager.h \
    ../../../Common/MetaPlugin.h \
    ../../../Common/Data.h \
    ../../../Common/DataManager.h \
    ../../../Common/FileData.h \
    ../../../Common/DataPlugin.h \
    ../../../Common/FileDataPlugin.h \
	../../../Common/AbstractManager.h \
    ../../NetworkPlugin.h \
    FileBaseServerMetaPlugin.h \
    FileServer.h \
	FileTransfertServer.h \
    FileNetworkPlugin.h

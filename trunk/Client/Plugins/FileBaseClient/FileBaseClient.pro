# -------------------------------------------------
# Project created by QtCreator 2009-04-09T19:51:57
# -------------------------------------------------
QT += sql \
    network
DEFINES += HORUS_CLIENT
TEMPLATE = lib
TARGET = FileBaseClientMetaPlugin
SOURCES += ../../../Common/DataImplementations/FileDataBase/FileDataBase.cpp \
    ../../../Common/DataImplementations/FileDataBase/FileBase.cpp \
    ../../../Common/DataImplementations/FileDataBase/FileDataBasePlugin.cpp \
    FileNetworkPlugin.cpp
HEADERS += ../../../Common/DataImplementations/FileDataBase/FileDataBase.h \
    ../../../Common/DataImplementations/FileDataBase/FileBase.h \
    ../../../Common/DataImplementations/FileDataBase/FileDataBasePlugin.h \
    ../../../Common/Plugin.h \
    ../../../Common/PluginManager.h \
    ../../../Common/MetaPlugin.h \
    ../../../Common/Data.h \
    ../../../Common/DataManager.h \
    ../../../Common/File.h \
    ../../../Common/FileData.h \
    ../../../Common/DataPlugin.h \
    ../../../Common/FileDataPlugin.h \
    ../../../Common/AbstractManager.h \
    ../../NetworkPlugin.h \
    FileNetworkPlugin.h \
    FileBaseClientMetaPlugin.h

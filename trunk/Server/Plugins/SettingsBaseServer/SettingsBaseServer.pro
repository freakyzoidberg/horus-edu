# -------------------------------------------------
# Project created by QtCreator 2009-04-09T19:51:57
# -------------------------------------------------
QT -= gui
QT += sql
DEFINES += HORUS_SERVER
TEMPLATE = lib
TARGET = SettingsBaseServerMetaPlugin
SOURCES +=   ../../../Common/DataImplementations/SettingsDataBase/SettingsDataBase.cpp \
            ../../../Common/DataImplementations/SettingsDataBase/SettingsDataBasePlugin.cpp
HEADERS += ../../../Common/DataImplementations/SettingsDataBase/SettingsDataBase.h \
          ../../../Common/DataImplementations/SettingsDataBase/SettingsDataBasePlugin.h \
         ../../../Common/Plugin.h \
        ../../../Common/PluginManager.h \
    .  ../../../Common/MetaPlugin.h \
      ../../../Common/Data.h \
     ../../../Common/DataManager.h \
    ../../../Common/SettingsData.h \
   ../../../Common/DataPlugin.h \
  ../../../Common/SettingsDataPlugin.h \
 ../../../Common/AbstractManager.h \
 SettingsBaseServerMetaPlugin.h

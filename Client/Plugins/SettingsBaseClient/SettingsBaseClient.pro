# -------------------------------------------------
# Project created by QtCreator 2009-04-09T19:51:57
# -------------------------------------------------
QT += sql
DEFINES += HORUS_CLIENT
TEMPLATE = lib
TARGET = SettingsBaseClientMetaPlugin
SOURCES +=   ../../../Common/DataImplementations/SettingsDataBase/SettingsDataBase.cpp \
            ../../../Common/DataImplementations/SettingsDataBase/SettingsDataBasePlugin.cpp
HEADERS += ../../../Common/DataImplementations/SettingsDataBase/SettingsDataBase.h \
          ../../../Common/DataImplementations/SettingsDataBase/SettingsDataBasePlugin.h \
         ../../../Common/Plugin.h \
        ../../../Common/PluginManager.h \
       ../../../Common/MetaPlugin.h \
      ../../../Common/Data.h \
     ../../../Common/DataManager.h \
    ../../../Common/SettingsData.h \
   ../../../Common/DataPlugin.h \
  ../../../Common/SettingsDataPlugin.h \
 SettingsBaseClientMetaPlugin.h
TRANSLATIONS = SettingsBaseClientMetaPlugin_en.ts \
			   SettingsBaseClientMetaPlugin_fr.ts

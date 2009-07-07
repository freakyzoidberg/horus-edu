# -------------------------------------------------
# Project created by QtCreator 2009-04-09T19:51:57
# -------------------------------------------------
QT -= gui
QT += sql
DEFINES += HORUS_SERVER
TEMPLATE = lib
TARGET = UserBaseServerMetaPlugin
SOURCES +=   ../../../Common/DataImplementations/UserDataBase/UserDataBase.cpp \
            ../../../Common/DataImplementations/UserDataBase/UserDataBasePlugin.cpp
HEADERS += ../../../Common/DataImplementations/UserDataBase/UserDataBase.h \
          ../../../Common/DataImplementations/UserDataBase/UserDataBasePlugin.h \
         ../../../Common/Plugin.h \
        ../../../Common/PluginManager.h \
    .  ../../../Common/MetaPlugin.h \
      ../../../Common/Data.h \
     ../../../Common/DataManager.h \
    ../../../Common/UserData.h \
   ../../../Common/DataPlugin.h \
  ../../../Common/UserDataPlugin.h \
  UserBaseServerMetaPlugin.h

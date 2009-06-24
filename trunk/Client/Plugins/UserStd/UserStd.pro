# -------------------------------------------------
# Project created by QtCreator 2009-04-09T19:51:57
# -------------------------------------------------
QT -= gui
QT += sql
DEFINES += HORUS_CLIENT
TEMPLATE = lib
SOURCES =   ../../../Common/DataImplementations/UserDataStd/UserDataStd.cpp \
           ../../../Common/DataImplementations/UserDataStd/UserDataStdPlugin.cpp
HEADERS = ../../../Common/DataImplementations/UserDataStd/UserDataStd.h \
         ../../../Common/DataImplementations/UserDataStd/UserDataStdPlugin.h \
        ../../../Common/Plugin.h \
       ../../../Common/PluginManager.h \
   .  ../../../Common/Data.h \
  .  ../../../Common/MetaPlugin.h \
    ../../../Common/UserData.h \
   ../../../Common/DataPlugin.h \
  ../../../Common/UserDataPlugin.h \
  UserStdMetaPlugin.h
DESTDIR = .
TARGET = $$qtLibraryTarget(ClientUserStdMetaPlugin)

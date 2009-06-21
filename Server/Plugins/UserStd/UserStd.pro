# -------------------------------------------------
# Project created by QtCreator 2009-04-09T19:51:57
# -------------------------------------------------
QT -= gui
QT += sql
DEFINES += HORUS_SERVER
TEMPLATE = lib
SOURCES =   ../../../Common/DataImplementations/UserDataStd/UserDataStd.cpp \
           ../../../Common/DataImplementations/UserDataStd/UserDataStdPlugin.cpp
HEADERS = ../../../Common/DataImplementations/UserDataStd/UserDataStd.h \
         ../../../Common/DataImplementations/UserDataStd/UserDataStdPlugin.h \
        ../../../Common/Plugin.h \
    .  ../../../Common/MetaPlugin.h \
      ../../../Common/Data.h \
     ../../../Common/UserData.h \
    ../../../Common/DataPlugin.h \
   ../../../Common/UserDataPlugin.h \
    UserStdMetaPlugin.h
DESTDIR = .
TARGET = $$qtLibraryTarget(UserStdMetaPlugin)

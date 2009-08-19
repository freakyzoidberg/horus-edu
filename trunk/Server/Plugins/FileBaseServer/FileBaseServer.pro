# -------------------------------------------------
# Project created by QtCreator 2009-04-09T19:51:57
# -------------------------------------------------
QT -= gui
QT += sql
DEFINES += HORUS_SERVER
TEMPLATE = lib
TARGET = FileBaseServerMetaPlugin
SOURCES +=   ../../../Common/DataImplementations/FileDataBase/FileDataBase.cpp \
            ../../../Common/DataImplementations/FileDataBase/FileDataBasePlugin.cpp
HEADERS += ../../../Common/DataImplementations/FileDataBase/FileDataBase.h \
          ../../../Common/DataImplementations/FileDataBase/FileDataBasePlugin.h \
         ../../../Common/Plugin.h \
        ../../../Common/PluginManager.h \
       ../../../Common/MetaPlugin.h \
      ../../../Common/Data.h \
     ../../../Common/DataManager.h \
    ../../../Common/FileData.h \
   ../../../Common/DataPlugin.h \
  ../../../Common/FileDataPlugin.h \
 ../../../Common/AbstractManager.h \
 FileBaseServerMetaPlugin.h

# -------------------------------------------------
# Project created by QtCreator 2009-04-09T19:51:57
# -------------------------------------------------
QT -= gui
QT += sql
DEFINES += HORUS_SERVER
TEMPLATE = lib
TARGET = TreeBaseServerMetaPlugin
SOURCES +=   ../../../Common/DataImplementations/TreeDataBase/TreeDataBase.cpp \
            ../../../Common/DataImplementations/TreeDataBase/TreeDataBasePlugin.cpp
HEADERS += ../../../Common/DataImplementations/TreeDataBase/TreeDataBase.h \
          ../../../Common/DataImplementations/TreeDataBase/TreeDataBasePlugin.h \
         ../../../Common/Plugin.h \
        ../../../Common/PluginManager.h \
    .  ../../../Common/MetaPlugin.h \
      ../../../Common/Data.h \
     ../../../Common/DataManager.h \
    ../../../Common/TreeData.h \
   ../../../Common/DataPlugin.h \
  ../../../Common/TreeDataPlugin.h \
  TreeBaseServerMetaPlugin.h

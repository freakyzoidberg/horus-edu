# -------------------------------------------------
# Project created by QtCreator 2009-04-09T19:51:57
# -------------------------------------------------
#QT -= gui
QT += sql
DEFINES += HORUS_SERVER
TEMPLATE = lib
TARGET = UserBaseServerMetaPlugin
SOURCES +=   ../../../Common/DataImplementations/WhiteBoardData/WhiteBoardData.cpp \
			../../../Common/DataImplementations/WhiteBoardData/WhiteBoardDataPlugin.cpp
HEADERS += ../../../Common/DataImplementations/WhiteBoardData/WhiteBoardData.h \
		  ../../../Common/DataImplementations/WhiteBoardData/WhiteBoardDataPlugin.h \
         ../../../Common/Plugin.h \
        ../../../Common/PluginManager.h \
       ../../../Common/MetaPlugin.h \
      ../../../Common/Data.h \
     ../../../Common/DataManager.h \
    ../../../Common/UserData.h \
   ../../../Common/DataPlugin.h \
  ../../../Common/UserDataPlugin.h \
 ../../../Common/AbstractManager.h \
 UserBaseServerMetaPlugin.h

# -------------------------------------------------
# Project created by QtCreator 2009-04-09T19:51:57
# -------------------------------------------------
QT += sql

TARGET = MarksBase

TEMPLATE = lib

DEFINES += HORUS_CLIENT

SOURCES += ../../../Common/DataImplementations/MarksDataBase/MarksDataBase.cpp \
    ../../../Common/DataImplementations/MarksDataBase/MarksDataBasePlugin.cpp \
      ../../DataListModel.cpp

HEADERS += ../../../Common/DataImplementations/MarksDataBase/MarksDataBase.h \
    ../../../Common/DataImplementations/MarksDataBase/MarksDataBasePlugin.h \
    ../../DataListModel.h \
    Implementation/MarksMetaPlugin.h \  
    ../../../Common/MarksData.h \
    ../../../Common/MarksDataPlugin.h \
    ../../../Common/TreeData.h \
    ../../../Common/TreeDataPlugin.h \
    ../../../Common/MetaPlugin.h \
    ../../../Common/Plugin.h \
    ../../../Common/PluginManager.h \
    ../../../Common/Data.h \
    ../../../Common/DataPlugin.h \
    ../../../Common/DataManager.h


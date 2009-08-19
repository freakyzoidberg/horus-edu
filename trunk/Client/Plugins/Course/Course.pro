# -------------------------------------------------
# Project created by QtCreator 2009-04-04T00:50:57
# -------------------------------------------------
QT += xml
TARGET = $$qtLibraryTarget(Course)
TEMPLATE = lib
DEFINES += HORUS_CLIENT
SOURCES += Implementation/Course.cpp \
           Implementation/CourseWidget.cpp
HEADERS += Implementation/Course.h \
           Implementation/CourseWidget.h \
           ../../DisplayablePlugin.h \
          ../../../Common/Plugin.h \
         ../../../Common/PluginManager.h \
        ../../../Common/MetaPlugin.h

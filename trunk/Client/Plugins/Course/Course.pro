# -------------------------------------------------
# Project created by QtCreator 2009-04-04T00:50:57
# -------------------------------------------------
QT += xml
TARGET = Course
TEMPLATE = lib
DEFINES += HORUS_CLIENT
SOURCES += Implementation/Course.cpp \
    Implementation/CourseWidget.cpp \
    whiteboard.cpp \
    items.cpp
HEADERS += Implementation/Course.h \
    Implementation/CourseWidget.h \
    Implementation/CourseMetaPlugin.h \
    ../../../Common/MetaPlugin.h \
    ../../DisplayablePlugin.h \
    ../../../Common/Plugin.h \
    ../../../Common/PluginManager.h \
    ../../../Common/AbstractManager.h \
    ../../../Common/MetaPlugin.h \
    whiteboard.h \
    items.h

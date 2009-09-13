# -------------------------------------------------
# Project created by QtCreator 2009-04-09T19:51:57
# -------------------------------------------------
QT += xml
TEMPLATE = lib
SOURCES += LessonManager.cpp \
    Lesson.cpp \
    XmlHandler.cpp \
    LessonModel.cpp
HEADERS += ILessonManager.h \
    LessonManager.h \
    Lesson.h \
    XmlHandler.h \
    LessonManagerMetaPlugin.h \
    ../../../Common/MetaPlugin.h \
    ../../../Common/Plugin.h \
    ../../../Common/Data.h \
    ../../../Common/TreeData.h \
    IController.h \
    LessonModel.h
INCLUDEPATH += .
DESTDIR = .
TARGET = TreeIcons.qrc
DEFINES += HORUS_CLIENT

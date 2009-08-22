# -------------------------------------------------
# Project created by QtCreator 2009-04-09T19:51:57
# -------------------------------------------------
QT += xml
TEMPLATE = lib
SOURCES += Implementation/LessonManager.cpp \
    Implementation/Lesson.cpp \
    Implementation/XmlHandler.cpp
HEADERS += ILessonManager.h \
    ILesson.h \
    Implementation/LessonManager.h \
    Implementation/Lesson.h \
    Implementation/XmlHandler.h \
    Implementation/LessonManagerMetaPlugin.h \
    ../../../Common/MetaPlugin.h \
    ../../../Common/Plugin.h \
    IController.h
INCLUDEPATH += .
DESTDIR = .
TARGET = LessonManager
RESOURCES += Implementation/TreeIcons.qrc
DEFINES += HORUS_CLIENT

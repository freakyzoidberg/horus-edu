# -------------------------------------------------
# Project created by QtCreator 2009-04-09T19:51:57
# -------------------------------------------------
QT += xml
TEMPLATE = lib
SOURCES += Implementation/LessonManager.cpp \
    Implementation/Lesson.cpp \
    LessonModel.cpp \
    ILesson.cpp \
    ILessonSection.cpp \
    ILessonDocument.cpp \
    Implementation/LessonSection.cpp \
    Implementation/LessonDocument.cpp
HEADERS += ILessonManager.h \
    LessonManagerMetaPlugin.h \
    ../../../Common/MetaPlugin.h \
    ../../../Common/Plugin.h \
    ../../../Common/Data.h \
    ../../../Common/FileData.h \
    ../../../Common/TreeData.h \
    ILesson.h \
    IDocumentController.h \
    LessonModel.h \
    Implementation/LessonManager.h \
    ILessonSection.h \
    ILessonDocument.h \
    Implementation/Lesson.h \
    ILessonData.h \
    Implementation/LessonSection.h \
    Implementation/LessonDocument.h
DEFINES += HORUS_CLIENT
RESOURCES += Implementation/TreeIcons.qrc
TARGET = LessonManager

# -------------------------------------------------
# Project created by QtCreator 2009-04-04T00:50:57
# -------------------------------------------------
QT += xml
TARGET = Course
TEMPLATE = lib
DEFINES += HORUS_CLIENT
SOURCES += Implementation/Course.cpp \
    Implementation/LessonDocument.cpp \
    Implementation/CourseWidget.cpp \
    Implementation/WhiteBoard.cpp \
    Implementation/Items.cpp \
    Implementation/WhiteBoardData.cpp
HEADERS += Implementation/Course.h \
    Implementation/CourseWidget.h \
    Implementation/CourseMetaPlugin.h \
    Implementation/LessonDocument.h \
    ../LessonManager/ILessonDocument.h \
    ../LessonManager/ILessonData.h \
    ../../../Common/MetaPlugin.h \
    ../../DisplayablePlugin.h \
    ../../../Common/Plugin.h \
    ../../../Common/PluginManager.h \
    ../../../Common/AbstractManager.h \
    ../../../../Common/FileDataPlugin.h \
    ../../../../Common/FileData.h \
    Implementation/WhiteBoard.h \
    Implementation/Items.h \
    Implementation/WhiteBoardData.h
RESOURCES += Implementation/Course.qrc

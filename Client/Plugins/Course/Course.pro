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
    ../../../Common/FileDataPlugin.h \
    ../../../Common/FileData.h \
    ../../../Common/Data.h \
    ../../../Common/DataPlugin.h \
    ../../../Common/UserData.h \
    ../../../Common/UserDataPlugin.h \
    Implementation/Items.h \
    Implementation/WhiteBoardData.h \
    Implementation/WhiteBoardItem.h \
    Implementation/WhiteBoard.h \
    IItems.h
RESOURCES += Implementation/Course.qrc

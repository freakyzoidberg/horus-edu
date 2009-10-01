# -------------------------------------------------
# Project created by QtCreator 2009-04-04T00:50:57
# -------------------------------------------------
QT += xml
TARGET = Course
TEMPLATE = lib
DEFINES += HORUS_CLIENT
SOURCES += ../../../Common/DataImplementations/WhiteBoardData/WhiteBoardData.cpp \
    ../../../Common/DataImplementations/WhiteBoardData/WhiteBoardDataPlugin.cpp \
    Implementation/LessonDocument.cpp \
    Implementation/CourseWidget.cpp \
    Implementation/WhiteBoard.cpp \
    Implementation/CreateWhiteBoard.cpp \
    Implementation/JoinWhiteBoard.cpp \
    Implementation/Items.cpp \
    Implementation/WhiteBoardModel.cpp \
    Implementation/Course.cpp
HEADERS += ../../../Common/MetaPlugin.h \
    ../../../Common/Plugin.h \
    ../../../Common/PluginManager.h \
    ../../../Common/AbstractManager.h \
    ../../../Common/FileDataPlugin.h \
    ../../../Common/FileData.h \
    ../../../Common/Data.h \
    ../../../Common/DataPlugin.h \
    ../../../Common/TreeData.h \
    ../../../Common/UserData.h \
    ../../../Common/UserDataPlugin.h \
    ../../../Common/DataImplementations/WhiteBoardData/WhiteBoardItem.h \
    ../../../Common/DataImplementations/WhiteBoardData/WhiteBoardData.h \
    ../../../Common/DataImplementations/WhiteBoardData/WhiteBoardDataPlugin.h \
    ../../DisplayablePlugin.h \
    ../LessonManager/ILessonDocument.h \
    ../LessonManager/ILessonData.h \
    ../LessonManager/ILessonSection.h \
    ../LessonManager/ILesson.h \
    Implementation/CourseWidget.h \
    Implementation/CourseMetaPlugin.h \
    Implementation/LessonDocument.h \
    Implementation/Items.h \
    Implementation/WhiteBoard.h \
    Implementation/CreateWhiteBoard.h \
    IItems.h \
    Implementation/WhiteBoardModel.h \
    Implementation/JoinWhiteBoard.h \
    Implementation/Course.h
RESOURCES += Implementation/Course.qrc
FORMS += Implementation/Ui/CreateWhiteBoard.ui \
    Implementation/Ui/JoinWhiteBoard.ui
TRANSLATIONS = Course_en.ts \
    Course_fr.ts

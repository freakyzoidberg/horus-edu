# -------------------------------------------------
# Project created by QtCreator 2009-06-06T07:17:56
# -------------------------------------------------
TARGET = TextController
TEMPLATE = lib
DEFINES += HORUS_CLIENT
SOURCES += Implementation/TextController.cpp
HEADERS += Implementation/TextController.h \
    Implementation/TextControllerMetaPlugin.h \
    ../LessonManager/ILessonDocument.h \
    ../LessonManager/ILessonData.h \
    ../LessonManager/ILesson.h \
    ../LessonManager/ILessonSection.h \
    ../../../Common/MetaPlugin.h \
    ../../../Common/Plugin.h

TRANSLATIONS = TextController_en.ts \
			   TextController_fr.ts

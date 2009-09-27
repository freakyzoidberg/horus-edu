#-------------------------------------------------
#
# Project created by tamere 2009-09-16T07:17:56
#
#-------------------------------------------------

TARGET = ImageController
TEMPLATE = lib

DEFINES += HORUS_CLIENT

SOURCES += Implementation/ImageController.cpp

HEADERS += Implementation/ImageController.h \
           Implementation/ImageControllerMetaPlugin.h \
           ../LessonManager/ILessonDocument.h \
           ../LessonManager/ILessonData.h \
           ../LessonManager/ILesson.h \
           ../LessonManager/ILessonSection.h \
           ../../../Common/MetaPlugin.h \
           ../../../Common/Plugin.h \
           ../../../Common/FileData.h \
           ../../../Common/FileDataPlugin.h \
           ../../../Common/Data.h \
           ../../../Common/DataPlugin.h \
           ../../../Common/UserData.h \
           ../../../Common/UserDataPlugin.h
TRANSLATIONS = ImageController_en.ts \
			   ImageController_fr.ts

# -------------------------------------------------
# Project created by QtCreator 2009-04-09T19:51:57
# -------------------------------------------------
QT += xml
TEMPLATE = lib
SOURCES += impl/LessonManager.cpp \
    impl/Lesson.cpp \
    impl/XmlHandler.cpp
HEADERS += ILessonManager.h \
    ILesson.h \
	impl/LessonManager.h \
    impl/LessonManager_global.h \
    impl/Lesson.h \
    impl/XmlHandler.h
INCLUDEPATH += .
DESTDIR = .
TARGET = $$qtLibraryTarget(lessonManagerModule)

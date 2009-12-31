# -------------------------------------------------
# Project created by QtCreator 2009-04-09T19:51:57
# -------------------------------------------------
QT += sql
TARGET = Marks
TEMPLATE = lib
DEFINES += HORUS_CLIENT
TRANSLATIONS = Marks_en.ts \
    Marks_fr.ts
RESOURCES += Implementation/Marks.qrc
SOURCES += Implementation/Marks.cpp \
    Implementation/MarksMainView.cpp \
    Implementation/subjectlist.cpp \
    Implementation/MarksManager.cpp \
    Implementation/InfoPanel.cpp \
    Implementation/ClassList.cpp \
    Implementation/MarksExamsList.cpp \
    Implementation/examslist.cpp
HEADERS += Implementation/Marks.h \
    Implementation/MarksMetaPlugin.h \
    ../../DisplayablePlugin.h \
    ../../../Common/MetaPlugin.h \
    ../../../Common/Plugin.h \
    Implementation/MarksMainView.h \
    Implementation/subjectlist.h \
    Implementation/MarksManager.h \
    Implementation/InfoPanel.h \
    Implementation/ClassList.h \
    Implementation/MarksExamsList.h \
    Implementation/examslist.h

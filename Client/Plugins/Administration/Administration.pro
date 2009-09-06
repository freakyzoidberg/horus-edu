# -------------------------------------------------
# Project created by QtCreator 2009-04-04T00:51:26
# -------------------------------------------------
QT += xml
TARGET = Administration
TEMPLATE = lib
DEFINES += HORUS_CLIENT
SOURCES += Implementation/Administration.cpp \
    Implementation/AdminMainFrame.cpp \
    Implementation/TeacherPage.cpp \
    Implementation/StudentsPage.cpp \
    Implementation/RoomPage.cpp
HEADERS += Implementation/Administration.h \
    Implementation/AdminMainFrame.h \
    Implementation/TeacherPage.h \
    Implementation/StudentsPage.h \
    Implementation/RoomPage.h \
    Implementation/AdministrationMetaPlugin.h \
    ../../../Common/MetaPlugin.h \
    ../../../Common/Plugin.h \
    ../../../NetworkPlugin.h \
    ../../DisplayablePlugin.h

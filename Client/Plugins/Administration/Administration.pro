# -------------------------------------------------
# Project created by QtCreator 2009-04-04T00:51:26
# -------------------------------------------------
QT += xml
TARGET = Administration
TEMPLATE = lib
DEFINES += HORUS_CLIENT
SOURCES += Implementation/Administration.cpp \
    Implementation/AdministrationFrame.cpp \
    Implementation/TreeFrame.cpp \
    Implementation/UserFrame.cpp \
    Implementation/ClassRoomFrame.cpp \
    Implementation/ClassFrame.cpp \
    Implementation/TeacherFrame.cpp \
    Implementation/FileFrame.cpp
HEADERS += Implementation/Administration.h \
    Implementation/AdministrationFrame.h \
    Implementation/TreeFrame.h \
    Implementation/UserFrame.h \
    Implementation/ClassRoomFrame.h \
    Implementation/ClassFrame.h \
    Implementation/TeacherFrame.h \
    Implementation/FileFrame.h \
    Implementation/AdministrationMetaPlugin.h \
    ../../../Common/MetaPlugin.h \
    ../../../Common/Plugin.h \
    ../../../Common/NetworkPlugin.h \
    ../../DisplayablePlugin.h
FORMS += Implementation/Ui/AdministrationFrame.ui \
    Implementation/Ui/UserFrame.ui \
    Implementation/Ui/ClassRoomFrame.ui \
    Implementation/Ui/ClassFrame.ui \
    Implementation/Ui/TeacherFrame.ui \
    Implementation/Ui/FileFrame.ui

# -------------------------------------------------
# Project created by QtCreator 2009-09-19T18:26:37
# -------------------------------------------------
QT += phonon
TARGET = Course
DEFINES += HORUS_CLIENT
TARGET = MediaController
TEMPLATE = lib
DEFINES += MEDIACONTROLLER_LIBRARY
SOURCES += Implementation/mediacontroller.cpp
HEADERS += Implementation/mediacontroller.h \
    Implementation/MediaControllerMetaPlugin.h \
    ../../../Common/MetaPlugin.h \
    ../../../Common/Plugin.h \
    ../../../Common/FileData.h \
    ../../../Common/FileDataPlugin.h \
    ../../../Common/Data.h \
    ../../../Common/DataPlugin.h \
    ../../../Common/UserData.h \
    ../../../Common/UserDataPlugin.h

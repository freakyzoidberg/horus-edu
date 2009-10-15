# -------------------------------------------------
# Project created by QtCreator 2009-04-04T00:55:11
# -------------------------------------------------
TARGET = News
TEMPLATE = lib
QT += webkit \
    network
DEFINES += HORUS_CLIENT
SOURCES += Implementation/News.cpp \
    Implementation/displayer.cpp \
    Implementation/newsplugin.cpp
HEADERS += Implementation/News.h \
    Implementation/NewsMetaPlugin.h \
    ../../../Common/MetaPlugin.h \
    ../../../Common/Plugin.h \
    ../../DisplayablePlugin.h \
    Implementation/displayer.h \
    Implementation/newsplugin.h
TRANSLATIONS = News_en.ts \
    News_fr.ts

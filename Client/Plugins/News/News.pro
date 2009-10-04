#-------------------------------------------------
#
# Project created by QtCreator 2009-04-04T00:55:11
#
#-------------------------------------------------

TARGET = News
TEMPLATE = lib

DEFINES += HORUS_CLIENT

SOURCES += Implementation/News.cpp

HEADERS += Implementation/News.h \
           Implementation/NewsMetaPlugin.h \
           ../../../Common/MetaPlugin.h \
		   ../../../Common/Plugin.h \
		   ../../DisplayablePlugin.h
TRANSLATIONS = News_en.ts \
News_fr.ts

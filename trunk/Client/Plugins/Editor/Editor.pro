#-------------------------------------------------
#
# Project created by QtCreator 2009-04-04T00:03:02
#
#-------------------------------------------------

QT       += xml

TARGET = Editor
TEMPLATE = lib

DEFINES += HORUS_CLIENT

SOURCES += Implementation/Editor.cpp

HEADERS += Implementation/Editor.h\
           Implementation/EditorMetaPlugin.h \
           ../../../Common/MetaPlugin.h \
           ../../DisplayablePlugin.h \
           ../../../Common/Plugin.h
TRANSLATIONS = Editor_en.ts \
			   Editor_fr.ts

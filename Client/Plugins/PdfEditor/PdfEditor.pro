# -------------------------------------------------
# Project created by QtCreator 2009-08-13T17:57:29
# -------------------------------------------------
QT += xml
TARGET = PdfEditor
TEMPLATE = lib
DEFINES += HORUS_CLIENT
SOURCES += Implementation/PdfEditor.cpp \
		   Implementation/TreeWidgetItem.cpp
HEADERS += Implementation/PdfEditor.h \
	       Implementation/TreeWidgetItem.h \
           Implementation/PdfEditorMetaPlugin.h \
           ../../../Common/MetaPlugin.h \
	       ../../../Common/Plugin.h

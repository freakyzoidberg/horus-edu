# -------------------------------------------------
# Project created by QtCreator 2009-05-02T13:15:50
# -------------------------------------------------
TEMPLATE = lib
LIBS += -lpoppler-qt4 \
    -lpoppler
DEFINES += HORUS_CLIENT
SOURCES += Implementation/PdfDisplayer.cpp \
		   Implementation/PdfRendering.cpp \
		   Implementation/PdfFile.cpp
HEADERS += Implementation/PdfDisplayer.h \
		   Implementation/PdfRendering.h \
		   Implementation/PdfFile.h \
		   IPdfRendering.h \
		   IPdfFile.h \
		   ../../../Common/Plugin.h \
		   ../../../Common/FileDataPlugin.h
INCLUDEPATH += . \
    ./Implementation \
    /usr/include/poppler \
    ../../ \
    ../../../Common
DESTDIR = .
TARGET = PdfDisplayer

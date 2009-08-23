# -------------------------------------------------
# Project created by QtCreator 2009-05-02T13:15:50
# -------------------------------------------------
TEMPLATE = lib
QT += xml \
    xmlpatterns
CONFIG       += plugin
win32 {
LIBS += -L./poppler/lib/ -lpoppler-qt4 \
    -L./poppler/lib/ -lpoppler
} unix {
LIBS += -lpoppler-qt4 \
     -lpoppler
}

DEFINES += HORUS_CLIENT
SOURCES += Implementation/PdfDisplayer.cpp \
		   Implementation/PdfRendering.cpp \
		   Implementation/PdfFile.cpp
HEADERS += Implementation/PdfDisplayer.h \
		   Implementation/PdfRendering.h \
		   Implementation/PdfFile.h \
           Implementation/PdfDisplayerMetaPlugin.h \
           ../../../Common/MetaPlugin.h \
		   IPdfRendering.h \
		   IPdfFile.h \
                   ../../../Common/Plugin.h
                #   ../../../Common/FileDataPlugin.h
INCLUDEPATH += . \
    ./include/poppler \
    ./Implementation \
    /usr/include/poppler \
    ../../ \
    ../../../Common
DESTDIR = .
# TARGET        = $$qtLibraryTarget(PdfDisplayer)
TARGET = PdfDisplayer

# -------------------------------------------------
# Project created by QtCreator 2009-05-02T13:15:50
# -------------------------------------------------
TEMPLATE = lib
QT += xml \
      xmlpatterns
CONFIG += plugin

# !!!!!!!!! poppler-glib only for MingGW, it will fail on Visual Studio
win32 {
LIBS += -L./Poppler/lib -lpoppler \
		-L./Poppler/lib -lpoppler-glib \
		-L./Poppler/lib -lpoppler-qt4
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
TRANSLATIONS = PdfDisplayer_en.ts \
			   PdfDisplayer_fr.ts

# -------------------------------------------------
# Project created by QtCreator 2009-05-02T13:15:50
# -------------------------------------------------
TEMPLATE = lib
LIBS += -lpoppler-qt4 \
    -lpoppler
DEFINES += DISPPDF_LIBRARY
SOURCES += implementation/disppdf.cpp \
    implementation/pdfFile.cpp
HEADERS += implementation/disppdf.h \
    implementation/pdfFile.h \
    IPdfRendering.h \
    IPdfFile.h \
    dispPDF_global.h
INCLUDEPATH += . \
    ./implementation \
    /usr/include/poppler \
    ../../ \
    ../../../Common
DESTDIR = .
TARGET = $$qtLibraryTarget(dispPDF)

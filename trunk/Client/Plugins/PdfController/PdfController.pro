# -------------------------------------------------
# Project created by QtCreator 2009-06-05T02:08:17
# -------------------------------------------------
TEMPLATE = lib

SOURCES += implementation/pdfcontroller.cpp
HEADERS += IPdfController.h \
    implementation/pdfcontroller.h \
    ../../dispPDF/IPdfFile.h \
    ../../dispPDF/implementation/dispPDF.h

INCLUDEPATH += . \
    ./implementation \
    ../../ \
    ../../../Common \
    ../../dispPDF/ \
    ../../dispPDF/implementation \
    /usr/include/poppler

DESTDIR = .

TARGET = $$qtLibraryTarget(pdfcontroller)

DESTDIR = .

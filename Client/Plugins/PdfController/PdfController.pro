# -------------------------------------------------
# Project created by QtCreator 2009-06-05T02:08:17
# -------------------------------------------------
TEMPLATE = lib

SOURCES += implementation/pdfcontroller.cpp
HEADERS += implementation/pdfcontroller.h

INCLUDEPATH += . \
    ./implementation \
    ../../ \
    ../../../Common \
    /usr/include/poppler

DESTDIR = .

TARGET = $$qtLibraryTarget(PdfController)

DESTDIR = .

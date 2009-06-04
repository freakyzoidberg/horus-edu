# -------------------------------------------------
# Project created by QtCreator 2009-06-05T02:08:17
# -------------------------------------------------
TEMPLATE = lib

SOURCES += implementation/pdfcontroller.cpp
HEADERS += IPdfController.h \
    implementation/pdfcontroller.h

INCLUDEPATH += . \
    ./implementation \
    ../../ \
    ../../../Common

DESTDIR = .

TARGET = $$qtLibraryTarget(pdfcontroller)

DESTDIR = .

# -------------------------------------------------
# Project created by QtCreator 2009-05-02T13:15:50
# -------------------------------------------------
TEMPLATE = lib

SOURCES += disppdf.cpp \
    dispPDFClient.cpp \
    dispPDFNetwork.cpp
HEADERS += disppdf.h \
    dispPDF_global.h \
    dispPDFClient.h \
    dispPDFNetwork.h
INCLUDEPATH += .
DESTDIR = .
TARGET = $$qtLibraryTarget(dispPDF)

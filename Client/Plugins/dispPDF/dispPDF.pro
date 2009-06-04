# -------------------------------------------------
# Project created by QtCreator 2009-05-02T13:15:50
# -------------------------------------------------
TEMPLATE = lib
LIBS += -lpoppler-qt4 \
    -lpoppler
SOURCES += implementation/disppdf.cpp \
    implementation/pdfFile.cpp
HEADERS += implementation/disppdf.h \
    implementation/pdfFile.h \
    IPdfRendering.h \
    IPdfFile.h
INCLUDEPATH += . \
    ./implementation \
    /usr/include/poppler \
    ../../ \
    ../../../Common
DESTDIR = .
TARGET = $$qtLibraryTarget(dispPDF)

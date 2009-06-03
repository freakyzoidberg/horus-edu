# -------------------------------------------------
# Project created by QtCreator 2009-05-02T13:15:50
# -------------------------------------------------
TEMPLATE = lib
LIBS += -lpoppler-qt4 \
    -lpoppler
SOURCES += implementation/disppdf.cpp \
    #implementation/dispPDFClient.cpp \
    #dispPDFNetwork.cpp \
    implementation/pdfRendering.cpp
   # metadata.cpp
HEADERS += implementation/disppdf.h \
    #implementation/dispPDFClient.h \
    #dispPDFNetwork.h \
    implementation/pdfRendering.h \
    IPdfRendering.h \
    # metadata.h \
    config.h
INCLUDEPATH += . \
    ./implementation \
    /usr/include/poppler \
    ../../ \
    ../../../Common
DESTDIR = .
TARGET = $$qtLibraryTarget(dispPDF)

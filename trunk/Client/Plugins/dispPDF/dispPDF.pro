# -------------------------------------------------
# Project created by QtCreator 2009-05-02T13:15:50
# -------------------------------------------------
TEMPLATE = lib
LIBS += -lpoppler-qt4 \
    -lpoppler
SOURCES += disppdf.cpp \
    dispPDFClient.cpp \
    dispPDFNetwork.cpp \
    pdfRendering.cpp
HEADERS += disppdf.h \
    dispPDF_global.h \
    dispPDFClient.h \
    dispPDFNetwork.h \
    pdfRendering.h
INCLUDEPATH += . \
    /usr/include/poppler
DESTDIR = .
TARGET = $$qtLibraryTarget(dispPDF)

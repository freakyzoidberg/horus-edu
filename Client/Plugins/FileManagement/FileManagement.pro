# -------------------------------------------------
# Project created by QtCreator 2009-04-04T00:47:29
# -------------------------------------------------
QT -= gui
QT += network
TARGET = FileManagement
TEMPLATE = lib
DEFINES += FILEMANAGEMENT_LIBRARY
SOURCES += Implementation/FileManagement.cpp \
           Implementation/File.cpp
HEADERS += Implementation/File.h \
           Implementation/FileManagement.h \
           FileManagement_global.h \
           IFile.h \
           IFilePlugin.h

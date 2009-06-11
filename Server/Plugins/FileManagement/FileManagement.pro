# -------------------------------------------------
# Project created by QtCreator 2009-04-09T19:51:57
# -------------------------------------------------
QT -= gui
QT += network sql
TEMPLATE = lib
SOURCES = FileManagement.cpp \
          FileServer.cpp \
          FileTransfert.cpp \
          ThreadFiles.cpp
HEADERS = FileManagement.h \
          FileServer.h \
          FileTransfert.h \
          ThreadFiles.h
DESTDIR = .
TARGET = $$qtLibraryTarget(FileManagement)

# -------------------------------------------------
# Project created by QtCreator 2009-04-06T14:49:51
# -------------------------------------------------
QT += network
QT -= gui
TARGET = ProtoTester
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += main.cpp \
    Socket.cpp \
    ../Common/CommFile.cpp \
    ../Common/CommFileInfo.cpp \
    ../Common/CommInit.cpp \
    ../Common/CommLogin.cpp \
    ../Common/CommSettings.cpp \
    ../Common/CommPacket.cpp \
    ../Common/CommPlugin.cpp \
    ../Common/CommSocket.cpp
HEADERS += Socket.h \
    ../Common/CommSocket.h

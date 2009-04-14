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
    ../Common/CommPacket.cpp \
    ../Common/CommModule.cpp \
    ../Common/CommLogin.cpp \
    ../Common/CommInit.cpp \
    ../Common/CommSocket.cpp
HEADERS += Socket.h \
    ../Common/CommPacket.h \
    ../Common/CommModule.h \
    ../Common/Defines.h \
    ../Common/CommSocket.h

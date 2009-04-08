# -------------------------------------------------
# Project created by QtCreator 2009-04-03T22:16:47
# -------------------------------------------------
QT += network \
    webkit \
    xml \
    phonon
TARGET = Horus_Client
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    ConnectionManager.cpp \
    ../Common/CommPacket.cpp \
    ../Common/CommModule.cpp \
    ../Common/CommMiniString.cpp \
    ../Common/CommLogin.cpp \
    ../Common/CommInit.cpp \
    ../Common/CommError.cpp
HEADERS += mainwindow.h \
    ClientAPI.h \
    ConnectionManager.h \
    ../Common/Defines.h \
    ../Common/CommPacket.h \
    ../Common/CommModule.h \
    ../Common/CommMiniString.h \
    ../Common/CommLogin.h \
    ../Common/CommInit.h \
    ../Common/CommError.h
FORMS += mainwindow.ui
OTHER_FILES += 

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
    ConnectionManager.cpp
HEADERS += mainwindow.h \
    ClientAPI.h \
    ../Common/Defines.h \
    ../Common/CommInit.h \
    ../Common/CommLogin.h \
    ../Common/CommModule.h \
    ../Common/CommRequest.h
    ConnectionManager.h
FORMS += mainwindow.ui
OTHER_FILES += 

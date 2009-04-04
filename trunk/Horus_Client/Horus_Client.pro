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
    ../Common/ModuleContainer.h \
    ../Common/CommunicationContainer.h \
    ../Common/Defines.h \
    ConnectionManager.h
FORMS += mainwindow.ui
OTHER_FILES += 

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
    Network.cpp
HEADERS += mainwindow.h \
    ClientAPI.h \
    ../Common/ModuleContainer.h \
    ../Common/CommunicationContainer.h \
    Network.h \
    ../Common/Defines.h
FORMS += mainwindow.ui
OTHER_FILES += 

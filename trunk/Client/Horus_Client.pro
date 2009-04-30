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
    NetworkManager.cpp \
    ../Common/CommPacket.cpp \
    ../Common/CommModule.cpp \
    ../Common/CommSocket.cpp \
    ../Common/CommLogin.cpp \
    ../Common/CommInit.cpp \
    ../Common/CommError.cpp \
    ClientApplication.cpp \
    PluginManager.cpp \
    StartEvent.cpp \
    StopEvent.cpp \
    LoadPluginEvent.cpp \
    UnloadPluginEvent.cpp \
    NetworkReceiveEvent.cpp \
    PacketManager.cpp
HEADERS += NetworkManager.h \
    ../Common/Defines.h \
    ../Common/CommPacket.h \
    ../Common/CommSocket.h \
    ../Common/CommModule.h \
    ../Common/CommLogin.h \
    ../Common/CommInit.h \
    ../Common/CommError.h \
    ClientApplication.h \
    IClientPlugin.h \
    PluginManager.h \
    StartEvent.h \
    StopEvent.h \
    LoadPluginEvent.h \
    UnloadPluginEvent.h \
    NetworkReceiveEvent.h \
    IPluginNetwork.h \
    PacketManager.h \
    ClientEvents.h \
    IClient.h
FORMS +=
OTHER_FILES += 

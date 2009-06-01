# -------------------------------------------------
# Project created by QtCreator 2009-04-03T22:16:47
# -------------------------------------------------
QT += network
TARGET = Horus_Client
TEMPLATE = app
SOURCES += main.cpp \
    NetworkManager.cpp \
    ../Common/CommPacket.cpp \
    ../Common/CommSocket.cpp \
    ../Common/CommLogin.cpp \
    ../Common/CommInit.cpp \
    ../Common/CommError.cpp \
    ClientApplication.cpp \
    PluginManager.cpp \
    PacketManager.cpp \
    ../Common/CommSettings.cpp \
    Loader.cpp \
    MainWindow.cpp \
    LoginDialog.cpp \
    ClientEvents.cpp \
    ConfigManager.cpp \
    ThreadNetwork.cpp \
    SettingsDialog.cpp \
    ../Common/CommPlugin.cpp \
    InterfaceClient.cpp \
    NetworkSender.cpp
HEADERS += NetworkManager.h \
    ../Common/Defines.h \
    ../Common/CommPacket.h \
    ../Common/PluginPacket.h \
    ../Common/CommSocket.h \
    ../Common/CommLogin.h \
    ../Common/CommInit.h \
    ../Common/CommError.h \
    ../Common/CommSettings.h \
    ../Common/CommPlugin.h \
                        \
    InterfaceClient.h \
    IPdfRendering.h \
    IMetadata.h \
    IMetaDataCreate.h \
    IClient.h \
    IClientPlugin.h \
    IPluginNetwork.h \
    INetworkSender.h \
                        \
    ClientApplication.h \
    PluginManager.h \
    PacketManager.h \
    ClientEvents.h \
    Loader.h \
    MainWindow.h \
    LoginDialog.h \
    ConfigManager.h \
    ThreadNetwork.h \
    SettingsDialog.h \
    ../Common/CommPlugin.h \
    InterfaceClient.h \
    IPluginNetwork.h \
    IDisplayable.h \
    IDisplayablePlugin.h \
    INetwork.h \
    INetworkReceiver.h \
    NetworkSender.h
FORMS += Ui/Loader.ui \
    Ui/MainWindow.ui \
    Ui/LoginDialog.ui \
    Ui/SettingsDialog.ui
RESOURCES += Ui/Loader.qrc \
    Ui/SettingsDialog.qrc \
    Ui/MainWindow.qrc
OTHER_FILES += 

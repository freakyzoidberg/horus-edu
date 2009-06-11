# -------------------------------------------------
# Project created by QtCreator 2009-04-03T22:16:47
# -------------------------------------------------
QT += network
TARGET = Horus_Client
TEMPLATE = app
SOURCES += main.cpp \
    ../Common/CommPacket.cpp \
    ../Common/CommSocket.cpp \
    ../Common/CommLogin.cpp \
    ../Common/CommInit.cpp \
    ../Common/CommError.cpp \
    ../Common/CommSettings.cpp \
    ../Common/CommPlugin.cpp \
    ../Common/PluginPacket.cpp \
    ClientApplication.cpp \
    NetworkManager.cpp \
    PluginManager.cpp \
    PacketManager.cpp \
    ConfigManager.cpp \
    Loader.cpp \
    MainWindow.cpp \
    LoginDialog.cpp \
    ClientEvents.cpp \
    ThreadNetwork.cpp \
    SettingsDialog.cpp \
    InterfaceClient.cpp \
    InterfaceNetwork.cpp \
    InterfaceDisplay.cpp \
    UserInfo.cpp \
    NotificationClient.cpp \
    DockMenu.cpp
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
    IMetadata.h \
    IMetaDataCreate.h \
    IClient.h \
    IClientPlugin.h \
    InterfaceClient.h \
    INetwork.h \
    INetworkPlugin.h \
    InterfaceNetwork.h \
    IDisplayable.h \
    IDisplayablePlugin.h \
    InterfaceDisplay.h \
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
    UserInfo.h \
    NotificationClient.h \
    DockMenu.h
FORMS += Ui/Loader.ui \
    Ui/MainWindow.ui \
    Ui/LoginDialog.ui \
    Ui/SettingsDialog.ui \
    Ui/DockMenu.ui
RESOURCES += Ui/Loader.qrc \
    Ui/SettingsDialog.qrc \
    Ui/MainWindow.qrc \
    Ui/DockMenu.qrc
RC_FILE = Client.rc

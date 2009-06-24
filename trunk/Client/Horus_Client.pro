# -------------------------------------------------
# Project created by QtCreator 2009-04-03T22:16:47
# -------------------------------------------------
QT += network
TARGET = Horus_Client
TEMPLATE = app
DEFINES += HORUS_CLIENT HORUS_CORE
SOURCES += main.cpp \
    ../Common/CommPacket.cpp \
    ../Common/CommSocket.cpp \
    ../Common/CommLogin.cpp \
    ../Common/CommInit.cpp \
    ../Common/CommError.cpp \
    ../Common/CommData.cpp \
    ../Common/CommPlugin.cpp \
    ../Common/PluginPacket.cpp \
    ../Common/DataManager.cpp \
    DisplayablePlugin.cpp \
    DataManagerClient.cpp \
    ClientApplication.cpp \
    NetworkManager.cpp \
    ThreadPlugin.cpp \
    PacketManager.cpp \
    ConfigManager.cpp \
    Loader.cpp \
    MainWindow.cpp \
    LoginDialog.cpp \
    ClientEvents.cpp \
    ThreadNetwork.cpp \
    SettingsDialog.cpp \
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
    ../Common/CommData.h \
    ../Common/CommPlugin.h \
    ../Common/PluginManager.h \
    ../Common/Plugin.h \
    ../Common/Data.h \
    ../Common/DataPlugin.h \
    ../Common/UserData.h \
    ../Common/UserDataPlugin.h \
    ../Common/NetworkPlugin.h \
    DisplayablePlugin.h \
    DataManagerClient.h \
    ClientApplication.h \
    PacketManager.h \
    ClientEvents.h \
    Loader.h \
    MainWindow.h \
    LoginDialog.h \
    ConfigManager.h \
    ThreadPlugin.h \
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

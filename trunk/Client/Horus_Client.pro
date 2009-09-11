# -------------------------------------------------
# Project created by QtCreator 2009-04-03T22:16:47
# -------------------------------------------------
QT += network
TARGET = Horus_Client
TEMPLATE = app
DEFINES += HORUS_CLIENT \
    HORUS_CORE
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
    DataManagerClient.cpp \
    ClientApplication.cpp \
    NetworkManager.cpp \
    PacketManager.cpp \
    LocalSettings.cpp \
    Loader.cpp \
    MainWindow.cpp \
    PluginManagerClient.cpp \
    LoginDialog.cpp \
    ClientEvents.cpp \
    SettingsDialog.cpp \
    UserInfo.cpp \
    NotificationClient.cpp \
    DockMenu.cpp \
    ManagerFactory.cpp \
    MetaManager.cpp \
    ManagerThread.cpp \
    Debugger.cpp
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
    ../Common/DataManager.h \
    ../Common/PluginManager.h \
    ../Common/Plugin.h \
    ../Common/Data.h \
    ../Common/DataPlugin.h \
    ../Common/UserData.h \
    ../Common/UserDataPlugin.h \
    ../Common/AbstractManager.h \
    NetworkPlugin.h \
    DisplayablePlugin.h \
    DataManagerClient.h \
    ClientApplication.h \
    PacketManager.h \
    ClientEvents.h \
    Loader.h \
    MainWindow.h \
    LoginDialog.h \
    LocalSettings.h \
    SettingsDialog.h \
    UserInfo.h \
    NotificationClient.h \
    PluginManagerClient.h \
    DockMenu.h \
    MetaManager.h \
    ManagerThread.h \
    ManagerFactory.h \
    ../Common/Notification.h \
    Debugger.h \
    DockMenuItem.h
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
QMAKE_EXTRA_TARGETS += plugintarget
POST_TARGETDEPS += .plugins
plugintarget.target = .plugins
win32 {
    plugintarget.commands = CopyPlugins.bat
}

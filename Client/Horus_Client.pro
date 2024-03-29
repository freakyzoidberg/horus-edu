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
	DataManagerClient.cpp \
    NetworkManager.cpp \
    HorusStyle.cpp \
    LocalSettings.cpp \
    MainWindow.cpp \
    PluginManagerClient.cpp \
    LoginDialog.cpp \
    SettingsDialog.cpp \
    UserInfo.cpp \
    Notification.cpp \
    Debugger.cpp \
    CacheManager.cpp \
    UserCache.cpp \
    LoginDialogItem.cpp \
	SecondaryThread.cpp \
	MainFrame/DragingWidget.cpp \
	MainFrame/MainFrame.cpp \
	MainFrame/MainFrameWidget.cpp
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
    ../Common/LocalSettings.h \
    NetworkPlugin.h \
    DisplayablePlugin.h \
	SmallDisplayablePlugin.h \
	DataManagerClient.h \
    HorusStyle.h \
    MainWindow.h \
    LoginDialog.h \
    SettingsDialog.h \
    UserInfo.h \
    Notification.h \
    PluginManagerClient.h \
    Debugger.h \
    CacheManager.h \
    UserCache.h \
    LoginDialogItem.h \
	SecondaryThread.h \
	MainFrame/DragingWidget.h \
	MainFrame/MainFrame.h \
	MainFrame/MainFrameWidget.h
FORMS += Ui/MainWindow.ui \
    Ui/SettingsDialog.ui \
	Ui/DockMenu.ui \
	MainFrame/Ui/MainFrameWidget.ui
RESOURCES += Ui/SettingsDialog.qrc \
    Ui/MainWindow.qrc \
	Ui/DockMenu.qrc \
	MainFrame/Ui/MainFrameWidget.qrc
RC_FILE = Client.rc
TRANSLATIONS = Horus_en.ts \
	Horus_fr.ts \
	MainFrame/MainFrame_en.ts \
	MainFrame/MainFrame_fr.ts
QMAKE_EXTRA_TARGETS += plugintarget
POST_TARGETDEPS += .plugins
plugintarget.target = .plugins
win32:plugintarget.commands = CopyPlugins.bat

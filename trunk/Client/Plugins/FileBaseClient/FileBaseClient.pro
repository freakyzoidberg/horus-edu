# -------------------------------------------------
# Project created by QtCreator 2009-04-09T19:51:57
# -------------------------------------------------
QT += sql \
    network
DEFINES += HORUS_CLIENT
TEMPLATE = lib
TARGET = FileBaseClientMetaPlugin
SOURCES += \
	../../../Common/DataImplementations/FileDataBase/FileDataBase.cpp \
	../../../Common/DataImplementations/FileDataBase/FileDataBasePlugin.cpp \
	../../../Common/DataImplementations/FileDataBase/FileTransfert.cpp \
	FileNetworkPlugin.cpp \
	FileTransfertClient.cpp \
	LibraryWidget.cpp \
	TransfertList.cpp
HEADERS += \
	../../../Common/DataImplementations/FileDataBase/FileDataBase.h \
    ../../../Common/DataImplementations/FileDataBase/FileDataBasePlugin.h \
	../../../Common/DataImplementations/FileDataBase/FileTransfert.h \
		../../../Common/Plugin.h \
    ../../../Common/PluginManager.h \
    ../../../Common/MetaPlugin.h \
    ../../../Common/Data.h \
    ../../../Common/DataManager.h \
    ../../../Common/FileData.h \
    ../../../Common/UserData.h \
    ../../../Common/TreeData.h \
    ../../../Common/DataPlugin.h \
    ../../../Common/FileDataPlugin.h \
	../../NetworkPlugin.h \
    ../../DisplayablePlugin.h \
    FileNetworkPlugin.h \
    FileBaseClientMetaPlugin.h \
	LibraryPlugin.h \
    LibraryWidget.h \
	FileTransfertClient.h \
	TransfertList.h
TRANSLATIONS = FileBaseClientMetaPlugin_en.ts \
    FileBaseClientMetaPlugin_fr.ts

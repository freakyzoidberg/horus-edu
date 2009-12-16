# -------------------------------------------------
# Project created by QtCreator 2009-04-09T19:51:57
# -------------------------------------------------
QT += sql \
    network
DEFINES += HORUS_CLIENT
TEMPLATE = lib
TARGET = FileBaseClientMetaPlugin
SOURCES += ../../../Common/DataImplementations/FileDataBase/FileDataBase.cpp \
    ../../../Common/DataImplementations/FileDataBase/FileDataBasePlugin.cpp \
    ../../../Common/DataImplementations/FileDataBase/FileTransfert.cpp \
    ../../DataListModel.cpp \
    FileNetworkPlugin.cpp \
    FileTransfertClient.cpp \
    LibrarySmallDisplayable.cpp \
    DownloadSmallDisplayable.cpp \
    TransfertList.cpp \
    LibraryFilterProxyModel.cpp \
    LibraryList.cpp \
    LibraryEdit.cpp \
    LibraryPlugin.cpp
HEADERS += ../../../Common/DataImplementations/FileDataBase/FileDataBase.h \
    ../../../Common/DataImplementations/FileDataBase/FileDataBasePlugin.h \
    ../../../Common/DataImplementations/FileDataBase/FileTransfert.h \
    ../../DataListModel.h \
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
    LibrarySmallDisplayable.h \
    DownloadSmallDisplayable.h \
    FileTransfertClient.h \
    TransfertList.h \
    TransfertPlugin.h \
    ../MainFrame/SmallDisplayablePlugin.h \
    LibraryFilterProxyModel.h \
    LibraryList.h \
    LibraryEdit.h
TRANSLATIONS = FileBaseClientMetaPlugin_en.ts \
    FileBaseClientMetaPlugin_fr.ts
RESOURCES += Icons/Icons.qrc

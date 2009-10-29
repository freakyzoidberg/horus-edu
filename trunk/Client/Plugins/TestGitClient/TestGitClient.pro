# -------------------------------------------------
# Project created by QtCreator 2009-04-04T00:47:29
# -------------------------------------------------
QT += xml
TARGET = TestGitClient
TEMPLATE = lib
DEFINES += HORUS_CLIENT
SOURCES += Implementation/TestGitWidget.cpp \
    Implementation/TestNetworkPlugin.cpp
HEADERS += Implementation/TestGit.h \
    Implementation/TestGitWidget.h \
    Implementation/TestGitMetaPlugin.h \
    ../../DisplayablePlugin.h \
    ../../../Common/Plugin.h \
    ../../../Common/PluginManager.h \
    ../../../Common/Data.h \
    ../../../Common/DataPlugin.h \
    ../../../Common/UserDataPlugin.h \
    ../../../Common/UserData.h \
    ../../../Common/TreeDataPlugin.h \
    ../../../Common/TreeData.h \
    ../../../Common/FileDataPlugin.h \
    ../../../Common/FileData.h \
    ../../../Common/SettingsDataPlugin.h \
    ../../../Common/SettingsData.h \
    ../../../Common/MetaPlugin.h \
    ../../NetworkPlugin.h \
    Implementation/TestNetworkPlugin.h
TRANSLATIONS = TestGitClient_en.ts \
			   TestGitClient_fr.ts

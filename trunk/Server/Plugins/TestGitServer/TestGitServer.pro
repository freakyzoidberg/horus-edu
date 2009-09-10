# -------------------------------------------------
# Project created by QtCreator 2009-04-04T00:47:29
# -------------------------------------------------
QT += xml \
	sql
TARGET = TestGitServer
TEMPLATE = lib
DEFINES += HORUS_SERVER
SOURCES += Implementation/TestNetworkPlugin.cpp
HEADERS += Implementation/TestGitMetaPlugin.h \
    ../../../Common/Plugin.h \
    ../../../Common/PluginManager.h \
    ../../../Common/Data.h \
    ../../../Common/UserData.h \
    ../../../Common/MetaPlugin.h \
    ../../NetworkPlugin.h \
    ../../../Common/AbstractManager.h \
    Implementation/TestNetworkPlugin.h

# -------------------------------------------------
# Project created by QtCreator 2009-04-04T00:47:29
# -------------------------------------------------
QT -= gui
QT += xml \
    sql \
    network
TARGET = MailServer
TEMPLATE = lib
DEFINES += HORUS_SERVER
SOURCES += Implementation/MailServerPlugin.cpp \
    Implementation/smtp.cpp
HEADERS += Implementation/MailServerMetaPlugin.h \
    ../../../Common/Plugin.h \
    ../../../Common/PluginManager.h \
    ../../../Common/Data.h \
    ../../../Common/UserData.h \
    ../../../Common/MetaPlugin.h \
    ../../NetworkPlugin.h \
    ../../../Common/AbstractManager.h \
    Implementation/MailServerPlugin.h \
    Implementation/smtp.h

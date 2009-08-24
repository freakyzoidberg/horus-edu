# -------------------------------------------------
# Project created by QtCreator 2009-04-09T19:51:57
# -------------------------------------------------
QT -= gui
QT += sql
QT += network
DEFINES += HORUS_SERVER
TEMPLATE = lib
TARGET = MailBaseServerMetaPlugin
SOURCES += ../../../Common/DataImplementations/MailDataBase/MailDataBase.cpp \
    ../../../Common/DataImplementations/MailDataBase/MailDataBasePlugin.cpp \
    ../../../Common/DataImplementations/MailDataBase/MailSender.cpp
HEADERS += ../../../Common/DataImplementations/MailDataBase/MailDataBase.h \
    ../../../Common/DataImplementations/MailDataBase/MailDataBasePlugin.h \
    ../../../Common/Plugin.h \
    ../../../Common/PluginManager.h \
    ../../../Common/MetaPlugin.h \
    ../../../Common/Data.h \
    ../../../Common/DataManager.h \
    ../../../Common/MailData.h \
    ../../../Common/DataPlugin.h \
    ../../../Common/MailDataPlugin.h \
    ../../../Common/AbstractManager.h \
    MailBaseServerMetaPlugin.h \
    ../../../Common/DataImplementations/MailDataBase/MailSender.h

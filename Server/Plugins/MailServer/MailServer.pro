# -------------------------------------------------
# Project created by QtCreator 2009-04-04T00:47:29
# -------------------------------------------------
QT -= gui
QT += xml \
    sql \
    network
TARGET = MailServerMetaPlugin
TEMPLATE = lib
DEFINES += HORUS_SERVER
SOURCES += Implementation/smtp.cpp \
    ../../../Common/DataImplementations/MailData/MailDataPlugin.cpp \
    ../../../Common/DataImplementations/MailData/MailData.cpp \
    Implementation/mime.cpp \
    Implementation/mail.cpp \
    Implementation/pop3.cpp \
    Implementation/pop_3.cpp \
    Implementation/MailNetwork.cpp
HEADERS += Implementation/MailServerMetaPlugin.h \
    ../../../Common/Plugin.h \
    ../../../Common/PluginManager.h \
    ../../../Common/Data.h \
    ../../../Common/UserData.h \
    ../../../Common/MetaPlugin.h \
    Implementation/smtp.h \
    ../../../Common/DataImplementations/MailData/MailItem.h \
    ../../../Common/DataImplementations/MailData/MailDataPlugin.h \
    ../../../Common/DataImplementations/MailData/MailData.h \
    ../../../Common/DataPlugin.h \
    ../../../Common/UserDataPlugin.h \
    ../../../Common/DataManager.h \
    ../../NetworkPlugin.h \
    Implementation/mime-types.h \
    Implementation/mime.h \
    Implementation/mail.h \
    Implementation/pop3.h \
    Implementation/pop_3.h \
    Implementation/MailNetwork.h

# -------------------------------------------------
# Project created by QtCreator 2009-04-04T00:03:02
# -------------------------------------------------
QT += xml
TARGET = Mail
TEMPLATE = lib
DEFINES += HORUS_CLIENT
SOURCES += Implementation/Mail.cpp \
    Implementation/MailPanel.cpp \
    Implementation/MailList.cpp \
    Implementation/MailForm.cpp
HEADERS += Implementation/Mail.h \
    Implementation/MailMetaPlugin.h \
    ../../../Common/MetaPlugin.h \
    ../../DisplayablePlugin.h \
    ../../../Common/Plugin.h \
    Implementation/MailPanel.h \
    \ \
    \ \
    \ \ # qmake configuration for linux-g++
    Implementation/MailList.h \
    Implementation/MailForm.h

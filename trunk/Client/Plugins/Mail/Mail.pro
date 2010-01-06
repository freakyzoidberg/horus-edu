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
    Implementation/MailForm.cpp \
    ../../../Common/DataImplementations/MailData/MailDataPlugin.cpp \
    ../../../Common/DataImplementations/MailData/MailData.cpp \
    Implementation/MailAbstractModel.cpp \
    Implementation/MailSmallDisplayable.cpp \
    Implementation/MailSmallWidget.cpp \
    Implementation/TextBrowser.cpp \
    ../../DataListModel.cpp \
    Implementation/MailsNetwork.cpp
HEADERS += Implementation/Mail.h \
    Implementation/MailMetaPlugin.h \
    ../../../Common/MetaPlugin.h \
    ../../DisplayablePlugin.h \
    ../../../Common/Plugin.h \
    ../../../Common/PluginManager.h \
    Implementation/MailPanel.h \
    Implementation/MailList.h \
    Implementation/MailForm.h \
    ../../../Common/DataImplementations/MailData/MailItem.h \
    ../../../Common/DataImplementations/MailData/MailDataPlugin.h \
    ../../../Common/DataImplementations/MailData/MailData.h \
    ../../../Common/DataPlugin.h \
    ../../../Common/Data.h \
    ../../../Common/DataManager.h \
    Implementation/MailAbstractModel.h \
    Implementation/MailSmallDisplayable.h \
    Implementation/MailSmallWidget.h \
    ../../SmallDisplayablePlugin.h \
    Implementation/TextBrowser.h \
    ../../DataListModel.h \
    Implementation/MailsNetwork.h
RESOURCES += Implementation/mailrc.qrc
TRANSLATIONS = Mail_en.ts \
    Mail_fr.ts

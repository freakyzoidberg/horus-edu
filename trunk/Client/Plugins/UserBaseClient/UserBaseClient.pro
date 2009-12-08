# -------------------------------------------------
# Project created by QtCreator 2009-04-09T19:51:57
# -------------------------------------------------

DEFINES +=		HORUS_CLIENT

TEMPLATE =		lib

TARGET =		UserBaseClientMetaPlugin

HEADERS +=		../../../Common/DataImplementations/UserDataBase/UserDataBase.h \
				../../../Common/DataImplementations/UserDataBase/UserDataBasePlugin.h \
				../../DataListModel.h \
				../../../Common/Plugin.h \
				../../../Common/PluginManager.h \
				../../../Common/MetaPlugin.h \
				../../../Common/Data.h \
				../../../Common/DataManager.h \
				../../../Common/UserData.h \
				../../../Common/DataPlugin.h \
				../../../Common/UserDataPlugin.h \
				Implementation/UserBaseClientMetaPlugin.h

SOURCES +=		../../../Common/DataImplementations/UserDataBase/UserDataBase.cpp \
				../../../Common/DataImplementations/UserDataBase/UserDataBasePlugin.cpp \
				../../DataListModel.cpp

RESOURCES +=	Implementation/Icons.qrc

TRANSLATIONS =	UserBaseClientMetaPlugin_en.ts \
				UserBaseClientMetaPlugin_fr.ts

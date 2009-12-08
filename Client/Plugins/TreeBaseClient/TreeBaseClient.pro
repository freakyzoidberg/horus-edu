# -------------------------------------------------
# Project created by QtCreator 2009-04-09T19:51:57
# -------------------------------------------------

DEFINES +=		HORUS_CLIENT

TEMPLATE =		lib

TARGET =		TreeBaseClientMetaPlugin

HEADERS +=		../../../Common/DataImplementations/TreeDataBase/TreeDataBase.h \
				../../../Common/DataImplementations/TreeDataBase/TreeDataBasePlugin.h \
				../../DataListModel.h \
				../../../Common/TreeData.h \
				../../../Common/TreeDataPlugin.h \
				../../../Common/MetaPlugin.h \
				../../../Common/Plugin.h \
				../../../Common/PluginManager.h \
				../../../Common/Data.h \
				../../../Common/DataPlugin.h \
				../../../Common/DataManager.h \
				../../../Common/UserData.h \
				Implementation/TreeModel.h \
				Implementation/TreeBaseClientMetaPlugin.h

SOURCES +=		../../../Common/DataImplementations/TreeDataBase/TreeDataBase.cpp \
				../../../Common/DataImplementations/TreeDataBase/TreeDataBasePlugin.cpp \
				../../DataListModel.cpp \
				Implementation/TreeModel.cpp

RESOURCES +=	Implementation/Icons.qrc

TRANSLATIONS =	TreeBaseClientMetaPlugin_en.ts \
				TreeBaseClientMetaPlugin_fr.ts

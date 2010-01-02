# -------------------------------------------------
# Project created by QtCreator 2009-04-09T19:51:57
# -------------------------------------------------

DEFINES +=		HORUS_CLIENT

TEMPLATE =		lib

TARGET =		Exams

HEADERS +=		../../DataListModel.h \
				../../../Common/TreeData.h \
				../../../Common/TreeDataPlugin.h \
				../../../Common/MetaPlugin.h \
				../../../Common/Plugin.h \
				../../../Common/PluginManager.h \
				../../../Common/Data.h \
				../../../Common/DataPlugin.h \
				../../../Common/DataManager.h \
				../../../Common/DataImplementations/ExamsDataBase/ExamsDataBase.h \
				../../../Common/DataImplementations/ExamsDataBase/ExamsDataBasePlugin.h \
				../../../Common/ExamsData.h \
				Implementation/ExamsMetaPlugin.h \
				../../../Common/ExamsDataPlugin.h \
				../../DisplayablePlugin.h

SOURCES +=		../../../Common/DataImplementations/ExamsDataBase/ExamsDataBase.cpp \
				../../../Common/DataImplementations/ExamsDataBase/ExamsDataBasePlugin.cpp \
				../../DataListModel.cpp

TRANSLATIONS =	Exams_en.ts \
				Exams_fr.ts

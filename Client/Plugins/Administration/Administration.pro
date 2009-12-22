# -------------------------------------------------
# Project created by QtCreator 2009-04-04T00:51:26
# -------------------------------------------------

TARGET =		Administration

TEMPLATE =		lib

DEFINES +=		HORUS_CLIENT

HEADERS +=		Implementation/Administration.h \
				Implementation/AdministrationMetaPlugin.h \
				../../../Common/MetaPlugin.h \
				../../../Common/Plugin.h \
				../../../Common/UserDataPlugin.h \
				../../../Common/UserData.h \
				../../../Common/TreeDataPlugin.h \
				../../../Common/TreeData.h \
				../../../Common/PluginManager.h \
				../../../Common/DataPlugin.h \
				../../../Common/Data.h \
				../../DisplayablePlugin.h \
				Implementation/ManageStructure.h \
				Implementation/ManageUser.h \
				Implementation/ListUser.h \
				Implementation/InformationsUser.h \
				Implementation/EditUser.h \
				Implementation/ManageClasses/AdmAddClassWidget.h \
				Implementation/ManageClasses/ClassListClass.h

SOURCES +=		Implementation/Administration.cpp \
				Implementation/ManageStructure.cpp \
				Implementation/ManageUser.cpp \
				Implementation/ListUser.cpp \
				Implementation/InformationsUser.cpp \
				Implementation/EditUser.cpp \
				Implementation/ManageClasses/AdmAddClassWidget.cpp \
				Implementation/ManageClasses/ClassListClass.cpp \

RESOURCES +=	Implementation/Administration.qrc

TRANSLATIONS =	Administration_en.ts \
				Administration_fr.ts

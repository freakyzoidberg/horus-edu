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
				Implementation/StructureElement.h \
				Implementation/StructureForm.h \
				Implementation/ElementSchool.h \
				Implementation/ElementClass.h \
				Implementation/ElementSubject.h \
				Implementation/ManageUser.h \
				Implementation/ListUser.h \
				Implementation/InformationsUser.h \
				Implementation/EditUser.h \

SOURCES +=		Implementation/Administration.cpp \
				Implementation/ManageStructure.cpp \
				Implementation/StructureElement.cpp \
				Implementation/StructureForm.cpp \
				Implementation/ElementSchool.cpp \
				Implementation/ElementClass.cpp \
				Implementation/ElementSubject.cpp \
				Implementation/ManageUser.cpp \
				Implementation/ListUser.cpp \
				Implementation/InformationsUser.cpp \
				Implementation/EditUser.cpp \

RESOURCES +=	Implementation/Administration.qrc

TRANSLATIONS =	Administration_en.ts \
				Administration_fr.ts

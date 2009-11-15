# -------------------------------------------------
# Project created by QtCreator 2009-04-04T00:51:26
# -------------------------------------------------
QT += xml
TARGET = Administrationv2
TEMPLATE = lib
DEFINES += HORUS_CLIENT
SOURCES += Implementation/Administration.cpp \
    Implementation/ManageParents/ManageParents.cpp \
    Implementation/ManageParents/DisplayParent.cpp \
    Implementation/ManageStudents/ManageStudents.cpp \
    Implementation/MainView.cpp \
    Implementation/ManageClasses/AdmAddClassWidget.cpp
HEADERS += Implementation/Administration.h \
    AdministrationMetaPlugin.h \
    ../../../Common/MetaPlugin.h \
    ../../../Common/Plugin.h \
    ../../DisplayablePlugin.h \
    ../../../Common/UserDataPlugin.h \
    ../../../Common/UserData.h \
    ../../../Common/TreeDataPlugin.h \
    ../../../Common/TreeData.h \
    ../../../Common/PluginManager.h \
    ../../../Common/DataPlugin.h \
    ../../../Common/Data.h \
    Implementation/ManageParents/ManageParents.h \
    Implementation/ManageParents/DisplayParent.h \
    Implementation/ManageStudents/ManageStudents.h \
    Implementation/MainView.h \
    Implementation/ManageClasses/AdmAddClassWidget.h

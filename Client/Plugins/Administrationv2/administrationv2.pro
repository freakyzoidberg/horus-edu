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
    Implementation/ManageParents/EditParent.cpp \
    Implementation/ManageParents/ParentsModel.cpp \
    Implementation/ManageStudents/ManageStudents.cpp \
    Implementation/MainView.cpp \
    Implementation/ManageClasses/AdmAddClassWidget.cpp \
    Implementation/ManageStudents/FormStudents.cpp \
    Implementation/ManageStudents/BasicInfos.cpp \
    Implementation/ManageStudents/ListSelection.cpp \
    Implementation/ManageStudents/Tools.cpp \
    Implementation/ManageStudents/ClassList.cpp \
    Implementation/ManageStudents/Socialinfos.cpp \
    Implementation/ManageStudents/Schoolinfos.cpp \
    Implementation/ManageStudents/Suiviinfos.cpp \
    Implementation/ManageStudents/Parentinfos.cpp \
    Implementation/ManageStudents/Infopanel.cpp
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
    Implementation/ManageParents/EditParent.h \
    Implementation/ManageParents/ParentsModel.h \
    Implementation/ManageStudents/ManageStudents.h \
    Implementation/MainView.h \
    Implementation/ManageClasses/AdmAddClassWidget.h \
    Implementation/ManageStudents/FormStudents.h \
    Implementation/ManageStudents/BasicInfos.h \
    Implementation/ManageStudents/ListSelection.h \
    Implementation/ManageStudents/Tools.h \
    Implementation/ManageStudents/ClassList.h \
    Implementation/ManageStudents/Socialinfos.h \
    Implementation/ManageStudents/Schoolinfos.h \
    Implementation/ManageStudents/Suiviinfos.h \
    Implementation/ManageStudents/Parentinfos.h \
    Implementation/ManageStudents/Infopanel.h
RESOURCES += Implementation/Icons.qrc
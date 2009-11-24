# -------------------------------------------------
# Project created by QtCreator 2009-04-04T00:51:26
# -------------------------------------------------
QT += xml
TARGET = Administrationv2
TEMPLATE = lib
DEFINES += HORUS_CLIENT
SOURCES += Implementation/Administration.cpp \
    Implementation/ManageParents/ManageParents.cpp \
    Implementation/ManageParents/ListParents.cpp \
    Implementation/ManageParents/DisplayParent.cpp \
    Implementation/ManageParents/EditParent.cpp \
    Implementation/ManageTeachers/ManageTeachers.cpp \
    Implementation/ManageTeachers/ListTeachers.cpp \
    Implementation/ManageTeachers/DisplayTeacher.cpp \
    Implementation/ManageTeachers/EditTeacher.cpp \
    Implementation/ManageAdministratives/ManageAdministratives.cpp \
    Implementation/ManageAdministratives/ListAdministratives.cpp \
    Implementation/ManageAdministratives/DisplayAdministrative.cpp \
    Implementation/ManageAdministratives/EditAdministrative.cpp \
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
    Implementation/ManageStudents/Infopanel.cpp \
    Implementation/ManageStudents/Scrollformstudent.cpp \
    Implementation/ManageClasses/ClassListClass.cpp
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
    Implementation/ManageTeachers/ManageTeachers.h \
    Implementation/ManageTeachers/ListTeachers.h \
    Implementation/ManageTeachers/DisplayTeacher.h \
    Implementation/ManageTeachers/EditTeacher.h \
    Implementation/ManageAdministratives/ManageAdministratives.h \
    Implementation/ManageAdministratives/ListAdministratives.h \
    Implementation/ManageAdministratives/DisplayAdministrative.h \
    Implementation/ManageAdministratives/EditAdministrative.h \
    Implementation/ManageParents/ManageParents.h \
    Implementation/ManageParents/ListParents.h \
    Implementation/ManageParents/DisplayParent.h \
    Implementation/ManageParents/EditParent.h \
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
    Implementation/ManageStudents/Infopanel.h \
    Implementation/ManageStudents/Scrollformstudent.h \
    Implementation/ManageClasses/ClassListClass.h
RESOURCES += Implementation/Icons.qrc
TRANSLATIONS = Administrationv2_en.ts \
    Administrationv2_fr.ts

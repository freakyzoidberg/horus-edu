# -------------------------------------------------
# Project created by QtCreator 2009-04-04T00:51:26
# -------------------------------------------------
QT += xml
TARGET = Administration
TEMPLATE = lib
DEFINES += HORUS_CLIENT
SOURCES += Implementation/Administration.cpp \
    Implementation/AdminMainFrame.cpp \
    Implementation/TeacherPage.cpp \
    Implementation/StudentsPage.cpp \
    Implementation/RoomPage.cpp \
    Implementation/AdminTree.cpp \
    Implementation/AdminModel.cpp \
    Implementation/UserModel.cpp
HEADERS += Implementation/Administration.h \
    Implementation/AdminMainFrame.h \
    Implementation/TeacherPage.h \
    Implementation/StudentsPage.h \
    Implementation/RoomPage.h \
    AdministrationMetaPlugin.h \
    ../../../Common/MetaPlugin.h \
    ../../../Common/Plugin.h \
    ../../../Common/AbstractManager.h \
    ../../DisplayablePlugin.h \
    ../../../Common/UserDataPlugin.h \
    ../../../Common/UserData.h \
    ../../../Common/TreeDataPlugin.h \
    ../../../Common/TreeData.h \
    ../../../Common/PluginManager.h \
    ../../../Common/DataPlugin.h \
    ../../../Common/Data.h \
    Implementation/StudentModel.h \
    Implementation/AdminTree.h \
    Implementation/AdminModel.h \
    Implementation/UserModel.h
RESOURCES += Implementation/AdminMainFrame.qrc

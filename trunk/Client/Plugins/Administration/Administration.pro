# -------------------------------------------------
# Project created by QtCreator 2009-04-04T00:51:26
# -------------------------------------------------
QT += xml
TARGET = Administration
TEMPLATE = lib
DEFINES += HORUS_CLIENT
SOURCES += Implementation/Administration.cpp \
    Implementation/AdminMainFrame.cpp \
    Implementation/RoomPage.cpp \
    Implementation/AdminTree.cpp \
    Implementation/AdminModel.cpp \
    Implementation/UserModel.cpp \
    Implementation/UserForm.cpp \
    Implementation/NodeInfo.cpp \
    Implementation/FileFram.cpp \
    Implementation/UserPage.cpp \
    Implementation/FilterModel.cpp \
    Implementation/AbsenceFrame.cpp \
    Implementation/NoteFrame.cpp \
    Implementation/BulletinFrame.cpp \
    Implementation/CourPanel.cpp \
    Implementation/ElevePanel.cpp
HEADERS += Implementation/Administration.h \
    Implementation/AdminMainFrame.h \
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
    Implementation/AdminTree.h \
    Implementation/AdminModel.h \
    Implementation/UserModel.h \
    Implementation/UserForm.h \
    Implementation/NodeInfo.h \
    Implementation/FileFram.h \
    Implementation/UserPage.h \
    Implementation/FilterModel.h \
    Implementation/AbsenceFrame.h \
    Implementation/NoteFrame.h \
    Implementation/BulletinFrame.h \
    Implementation/CourPanel.h \
    Implementation/ElevePanel.h
RESOURCES += Implementation/AdminMainFrame.qrc
TRANSLATIONS = Administration_en.ts \
    Administration_fr.ts

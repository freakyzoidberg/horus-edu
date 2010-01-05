# -------------------------------------------------
# Project created by QtCreator 2009-09-19T18:26:37
# -------------------------------------------------
QT += phonon
TARGET = AudioController
DEFINES += HORUS_CLIENT
TARGET = AudioController
TEMPLATE = lib
DEFINES += AUDIOCONTROLLER_LIBRARY
SOURCES += Implementation/AudioController.cpp \
    Implementation/audioplayer.cpp
HEADERS += Implementation/AudioController.h \
    Implementation/AudioControllerMetaPlugin.h \
    ../../../Common/MetaPlugin.h \
    ../../../Common/Plugin.h \
    ../../../Common/FileData.h \
    ../../../Common/FileDataPlugin.h \
    ../../../Common/Data.h \
    ../../../Common/DataPlugin.h \
    ../../../Common/UserData.h \
    ../../../Common/UserDataPlugin.h \
	../../../Common/DataImplementations/WhiteBoardData/WhiteBoardItem.h \
    Implementation/audioplayer.h
RESOURCES += Implementation/AudioController.qrc
TRANSLATIONS = AudioController_en.ts \
			   AudioController_fr.ts

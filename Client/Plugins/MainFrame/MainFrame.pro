# -------------------------------------------------
# Project created by QtCreator 2009-04-04T00:47:29
# -------------------------------------------------
QT += xml
TARGET = MainFrame
TEMPLATE = lib
DEFINES += HORUS_CLIENT
SOURCES += Src/MainFrame.cpp \
           Src/MainFrameWidget.cpp
HEADERS += Src/MainFrame.h \
           Src/MainFrameWidget.h \
           MainFrameMetaPlugin.h \
           ../../DisplayablePlugin.h \
          ../../../Common/Plugin.h \
         ../../../Common/PluginManager.h \
        ../../../Common/UserData.h \
       ../../../Common/Data.h \
      ../../../Common/DataPlugin.h \
     ../../../Common/UserDataPlugin.h \
    ../../../Common/TreeDataPlugin.h \
   ../../../Common/MetaPlugin.h \
  ../../../Common/AbstractManager.h
FORMS += Ui/MainFrameWidget.ui
RESOURCES += Ui/MainFrameWidget.qrc

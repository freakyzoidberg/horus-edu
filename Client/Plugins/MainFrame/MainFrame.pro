# -------------------------------------------------
# Project created by QtCreator 2009-04-04T00:47:29
# -------------------------------------------------
QT += xml
TARGET = MainFrame
TEMPLATE = lib
DEFINES += HORUS_CLIENT
SOURCES += Implementation/MainFrame.cpp \
           Implementation/MainFrameWidget.cpp
HEADERS += Implementation/MainFrame.h \
           Implementation/MainFrameWidget.h \
           Implementation/MainFrameMetaPlugin.h \
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
FORMS += Implementation/Ui/MainFrameWidget.ui
RESOURCES += Implementation/Ui/MainFrameWidget.qrc

# -------------------------------------------------
# Project created by QtCreator 2009-10-09T18:57:51
# -------------------------------------------------
TARGET = Calendar

TEMPLATE = lib

DEFINES += HORUS_CLIENT

TEMPLATE = lib

DEFINES += CALENDAR_LIBRARY

SOURCES += Implementation/calendar.cpp \
    Implementation/CalendarMainFrame.cpp \
    Implementation/CalendarWidget.cpp \
    Implementation/CalendarCore.cpp \
    Implementation/addeventwidget.cpp \
    Implementation/addeventwindows.cpp \
    Implementation/calendarcontrolswidget.cpp

HEADERS += Implementation/calendar.h \
    Implementation/CalendarMetaPlugin.h \
    ../../../Common/EventData.h \
    ../../../Common/EventDataPlugin.h \
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
    Implementation/CalendarMainFrame.h \
    Implementation/CalendarWidget.h \
    Implementation/CalendarCore.h \
    Implementation/addeventwidget.h \
    Implementation/addeventwindows.h \
    Implementation/calendarcontrolswidget.h

RESOURCES += Calendar.qrc

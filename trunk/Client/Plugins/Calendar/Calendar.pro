# -------------------------------------------------
# Project created by QtCreator 2009-10-09T18:57:51
# -------------------------------------------------
TARGET = Calendar
TEMPLATE = lib
DEFINES += HORUS_CLIENT
TEMPLATE = lib
DEFINES += CALENDAR_LIBRARY

SOURCES += Implementation/calendar.cpp \
        ../../../Common/DataImplementations/CalendarData/CalendarData.cpp \
        ../../../Common/DataImplementations/CalendarData/CalendarDataPlugin.cpp

HEADERS += Implementation/calendar.h \
    Implementation/CalendarMetaPlugin.h \
     ../../../Common/DataImplementations/CalendarData/CalendarItem.h \
    ../../../Common/DataImplementations/CalendarData/CalendarData.h \
    ../../../Common/DataImplementations/CalendarData/CalendarDataPlugin.h

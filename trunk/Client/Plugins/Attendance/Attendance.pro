#-------------------------------------------------
#
# Project created by QtCreator 2009-04-04T00:03:02
#
#-------------------------------------------------

QT       += xml

TARGET = Attendance
TEMPLATE = lib

DEFINES += HORUS_CLIENT

SOURCES += Implementation/Attendance.cpp

HEADERS += Implementation/Attendance.h\
           ../../DisplayablePlugin.h \
           ../../../Common/MetaPlugin.h \
           Implementation/AttendanceMetaPlugin.h \
           ../../../Common/Plugin.h
TRANSLATIONS = Attendance_en.ts \
			   Attendance_fr.ts

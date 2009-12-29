# -------------------------------------------------
# Project created by QtCreator 2009-04-04T00:03:02
# -------------------------------------------------
QT += xml
TARGET = Attendance
TEMPLATE = lib
DEFINES += HORUS_CLIENT
SOURCES += Implementation/Attendance.cpp \
    Implementation/CourPanel.cpp \
    Implementation/AttendanceFrame.cpp
HEADERS += Implementation/Attendance.h \
    ../../DisplayablePlugin.h \
    ../../../Common/MetaPlugin.h \
    Implementation/AttendanceMetaPlugin.h \
    ../../../Common/Plugin.h \
    Implementation/CourPanel.h \
    Implementation/AttendanceFrame.h
TRANSLATIONS = Attendance_en.ts \
    Attendance_fr.ts

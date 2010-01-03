# -------------------------------------------------
# Project created by QtCreator 2009-04-04T00:03:02
# -------------------------------------------------
QT += xml
TARGET = Attendance
TEMPLATE = lib
DEFINES += HORUS_CLIENT
SOURCES += Implementation/Attendance.cpp \
    Implementation/CourPanel.cpp \
    Implementation/AttendanceFrame.cpp \
    Implementation/UserPerClass.cpp \
    Implementation/ListUser.cpp \
    Implementation/InformationsUser.cpp \
    Implementation/AddAttendance.cpp \
    Implementation/ShowAttendance.cpp
HEADERS += Implementation/Attendance.h \
    ../../DisplayablePlugin.h \
    ../../../Common/MetaPlugin.h \
    Implementation/AttendanceMetaPlugin.h \
    ../../../Common/Plugin.h \
    Implementation/CourPanel.h \
    Implementation/AttendanceFrame.h \
    Implementation/UserPerClass.h \
    Implementation/ListUser.h \
    Implementation/InformationsUser.h \
    Implementation/AddAttendance.h \
    Implementation/ShowAttendance.h
TRANSLATIONS = Attendance_en.ts \
    Attendance_fr.ts
RESOURCES += Implementation/Icons.qrc

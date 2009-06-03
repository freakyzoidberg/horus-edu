# -------------------------------------------------
# Project created by QtCreator 2009-04-04T00:51:26
# -------------------------------------------------
QT += xml
TARGET = Administration
TEMPLATE = lib
DEFINES += ADMINISTRATION_LIBRARY
SOURCES += AdministrationPlugin.cpp \
    AdminFram.cpp \
    UserManager.cpp \
    TreeFram.cpp \
    UserFram.cpp
HEADERS += AdministrationPlugin.h \
    AdminFram.h \
    UserManager.h \
    TreeManager.h \
    TreeFram.h \
    UserFram.h
FORMS += AdminFram.ui \
    TreeFram.ui \
    UserFram.ui

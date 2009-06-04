# -------------------------------------------------
# Project created by QtCreator 2009-06-05T04:05:53
# -------------------------------------------------
QT -= gui
TARGET = TreeManagement
TEMPLATE = lib
DEFINES += TREEMANAGEMENT_LIBRARY
SOURCES += Implementation/TreeManagement.cpp \
    Implementation/Tree.cpp \
    Implementation/TreeModel.cpp
HEADERS += Implementation/TreeManagement.h \
    Implementation/Tree.h \
    Implementation/TreeModel.h \
    ITree.h \
    TreeManagement_global.h \
    ITreePlugin.h

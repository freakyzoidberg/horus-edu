# -------------------------------------------------
# Project created by QtCreator 2009-42-04T00:55:11
# -------------------------------------------------

TARGET =		TimeTable

TEMPLATE =		lib

DEFINES +=		HORUS_CLIENT

HEADERS +=		Implementation/TimeTable.h \
				../../../Common/MetaPlugin.h \
				../../../Common/Plugin.h \
				../../DisplayablePlugin.h \
				Implementation/MainView.h \
				Implementation/EdtScene.h \
				Implementation/AdmListEdt.h \
				Implementation/ManageEdt.h \
				Implementation/EdtPlanning.h \
				Implementation/EdtSceneProxyWidget.h \
				TimeTableMetaPlugin.h \
				Implementation/EdtWidget.h \
				Implementation/EditScheduleEvent.h \
				Implementation/EditSchedule.h \
				Implementation/EditException.h \
				Implementation/AdmClassListSelection.h \
				Implementation/InfoPanel.h \
				Implementation/EdtTimer.h \
				Implementation/TimeTableSmallDisplayable.h \
				Implementation/DayLessons.h \
				../../SmallDisplayablePlugin.h

SOURCES +=		Implementation/TimeTable.cpp \
				Implementation/MainView.cpp \
				Implementation/EdtScene.cpp \
				Implementation/AdmListEdt.cpp \
				Implementation/ManageEdt.cpp \
				Implementation/EdtPlanning.cpp \
				Implementation/EdtSceneProxyWidget.cpp \
				Implementation/EdtWidget.cpp \
				Implementation/EditScheduleEvent.cpp \
				Implementation/EditSchedule.cpp \
				Implementation/EditException.cpp \
				Implementation/AdmClassListSelection.cpp \
				Implementation/Infopanel.cpp \
				Implementation/EdtTimer.cpp \
				Implementation/TimeTableSmallDisplayable.cpp \
				Implementation/DayLessons.cpp

RESOURCES +=	Implementation/TimeTable.qrc

TRANSLATIONS =	TimeTable_en.ts \
				TimeTable_fr.ts

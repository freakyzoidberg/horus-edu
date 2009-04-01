#ifndef CALENDAR_GLOBAL_H
#define CALENDAR_GLOBAL_H

#include <QtCore/qglobal.h>

#include "../../module.h"

#if defined(CALENDAR_LIBRARY)
#  define CALENDARSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CALENDARSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // CALENDAR_GLOBAL_H

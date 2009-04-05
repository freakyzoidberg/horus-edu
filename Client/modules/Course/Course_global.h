#ifndef COURSE_GLOBAL_H
#define COURSE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(COURSE_LIBRARY)
#  define COURSESHARED_EXPORT Q_DECL_EXPORT
#else
#  define COURSESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // COURSE_GLOBAL_H

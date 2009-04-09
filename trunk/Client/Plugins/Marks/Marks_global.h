#ifndef MARKS_GLOBAL_H
#define MARKS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MARKS_LIBRARY)
#  define MARKSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MARKSSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MARKS_GLOBAL_H

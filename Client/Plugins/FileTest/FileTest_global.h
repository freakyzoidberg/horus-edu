#ifndef FILETEST_GLOBAL_H
#define FILETEST_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(FILETEST_LIBRARY)
#  define FILETESTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define FILETESTSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // FILETEST_GLOBAL_H
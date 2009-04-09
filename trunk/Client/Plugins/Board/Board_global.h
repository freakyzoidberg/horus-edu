#ifndef BOARD_GLOBAL_H
#define BOARD_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(BOARD_LIBRARY)
#  define BOARDSHARED_EXPORT Q_DECL_EXPORT
#else
#  define BOARDSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // BOARD_GLOBAL_H

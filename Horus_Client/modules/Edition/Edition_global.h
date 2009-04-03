#ifndef EDITION_GLOBAL_H
#define EDITION_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(EDITION_LIBRARY)
#  define EDITIONSHARED_EXPORT Q_DECL_EXPORT
#else
#  define EDITIONSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // EDITION_GLOBAL_H

#ifndef EDITPDF_GLOBAL_H
#define EDITPDF_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(EDITPDF_LIBRARY)
#  define EDITPDFSHARED_EXPORT Q_DECL_EXPORT
#else
#  define EDITPDFSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // EDITPDF_GLOBAL_H

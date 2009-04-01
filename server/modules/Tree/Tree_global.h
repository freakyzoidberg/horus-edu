#ifndef TREE_GLOBAL_H
#define TREE_GLOBAL_H

#include <QtCore/qglobal.h>

#include "../../module.h"

#if defined(TREE_LIBRARY)
#  define TREESHARED_EXPORT Q_DECL_EXPORT
#else
#  define TREESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // TREE_GLOBAL_H

#ifndef TREEMANAGEMENT_GLOBAL_H
#define TREEMANAGEMENT_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QtPlugin>

#include "../../IClientPlugin.h"
#include "../../INetworkPlugin.h"
#include "ITreePlugin.h"

#if defined(TREEMANAGEMENT_LIBRARY)
#  define TREEMANAGEMENTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define TREEMANAGEMENTSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // TREEMANAGEMENT_GLOBAL_H

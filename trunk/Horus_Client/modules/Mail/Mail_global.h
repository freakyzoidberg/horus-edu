#ifndef MAIL_GLOBAL_H
#define MAIL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MAIL_LIBRARY)
#  define MAILSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MAILSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MAIL_GLOBAL_H

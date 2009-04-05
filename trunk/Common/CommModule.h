#ifndef COMMMODULE_H
#define COMMMODULE_H

#include <QDataStream>

#include "Defines.h"

/*!
 * If the "messageType" of the "CommunicationContainer" is "MODULE_COMM"
 * there is this class inside "content".
 * it's for the comunication between a module client and a module server
 */
class CommModule
{
public:
    char    modSrc  [MODULE_NAME_SIZE   ];
    char    verSrc  [MODULE_VERSION_SIZE];
    char    modDest [MODULE_NAME_SIZE   ];
    char    verCont [MODULE_VERSION_SIZE];

    quint32 sizeCont;
};

QDataStream& operator<<(QDataStream& ds, CommModule& lc);
QDataStream& operator>>(QDataStream& ds, CommModule& lc);

#endif // COMMMODULE_H

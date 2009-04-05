#ifndef COMMMODULE_H
#define COMMMODULE_H

#include <QDataStream>

#include "CommMiniString.h"

/*!
 * If the "messageType" of the "CommunicationContainer" is "MODULE_COMM"
 * there is this class inside "content".
 * it's for the comunication between a module client and a module server
 */
class CommModule
{
public:
    CommModule();

    /*!
     * Version of This object
     */
    quint8          ver;

    CommMiniString  moduleSource;
    CommMiniString  moduleSourceVersion;
    CommMiniString  moduleDestination;
};

QDataStream& operator<<(QDataStream&, CommModule&);
QDataStream& operator>>(QDataStream&, CommModule&);

#endif // COMMMODULE_H

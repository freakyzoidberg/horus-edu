#ifndef COMMMODULE_H
#define COMMMODULE_H

#include "CommPacket.h"
#include "ModulePacket.h"

/*!
 * If the "messageType" of the "CommunicationContainer" is "MODULE_COMM"
 * there is this class inside "content".
 * it's for the comunication between a module client and a module server
 */
class CommModule : public CommPacket
{
public:
    CommModule(QByteArray&);
    CommModule(const ModulePacket&);
    const QByteArray getPacket();
    ModulePacket packet;
};

QDebug operator<<(QDebug, CommModule&);

#endif // COMMMODULE_H

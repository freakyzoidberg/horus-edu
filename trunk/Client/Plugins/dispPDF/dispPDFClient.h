#ifndef DISPPDFCLIENT_H
#define DISPPDFCLIENT_H

#include <QObject>

#include "../../IClient.h"
#include "../../IClientPlugin.h"
#include "../../../Common/ModulePacket.h"

class   dispPDFClient : public QObject, public Iclient
{
 Q_OBJECT
 Q_INTERFACES(Iclient)

public:
    void            sendPacket(const ModulePacket& packet) const;
    void            recvPacket(const ModulePacket& packet) const;
    IClientPlugin*  getPlugin(const char* name) const;
};

#endif // DISPPDFCLIENT_H

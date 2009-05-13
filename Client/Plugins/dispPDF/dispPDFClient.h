#ifndef DISPPDFCLIENT_H
#define DISPPDFCLIENT_H

#include <QObject>

#include "../../IClient.h"
#include "../../IClientPlugin.h"
#include "../../../Common/ModulePacket.h"

class   dispPDFClient : public QObject, public IClient
{
 Q_OBJECT
 Q_INTERFACES(IClient)

public:  
       void            sendPacket(const ModulePacket& packet) const;
       void            recvPacket(const ModulePacket& packet) const;
       IClientPlugin*  getPlugin(const QByteArray name) const;
};

#endif // DISPPDFCLIENT_H

#ifndef DISPPDFCLIENT_H
#define DISPPDFCLIENT_H

#include <QObject>

#include <IClient.h>
#include <IClientPlugin.h>
#include <PluginPacket.h>

//! Implementation of the interface IClient
class   dispPDFClient : public QObject, public IClient
{
 //Q_OBJECT
 //Q_INTERFACES(IClient)

public:  
       void            sendPacket(const PluginPacket& packet) const;
       void            recvPacket(const PluginPacket& packet) const;
       IClientPlugin*  getPlugin(const QByteArray name) const;
};

#endif // DISPPDFCLIENT_H

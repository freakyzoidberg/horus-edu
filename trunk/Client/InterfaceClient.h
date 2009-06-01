#ifndef INTERFACECLIENT_H
#define INTERFACECLIENT_H

#include "IClient.h"
#include "../Common/PluginPacket.h"
#include "../Common/CommPlugin.h"
#include "IClientPlugin.h"
#include "ClientApplication.h"
#include "PluginManager.h"
#include "ThreadNetwork.h"

class InterfaceClient : public IClient
{
    public:
        InterfaceClient(IClientPlugin *p, ClientApplication *father);
        IClientPlugin   *getPlugin(const QByteArray name) const;

    private:
        IClientPlugin       *plugin;
        ClientApplication   *parent;
        PluginManager       *pM;
};

#endif // INTERFACECLIENT_H

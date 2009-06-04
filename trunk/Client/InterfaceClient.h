#ifndef INTERFACECLIENT_H
#define INTERFACECLIENT_H

#include "IClient.h"
#include "IClientPlugin.h"
#include "ClientApplication.h"
#include "PluginManager.h"

class InterfaceClient : public IClient
{
    public:
        InterfaceClient(PluginManager *pM);
        IClientPlugin   *getPlugin(const QByteArray name) const;

    private:
        PluginManager       *pM;
};

#endif // INTERFACECLIENT_H

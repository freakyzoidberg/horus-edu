#ifndef IPLUGINNETWORK_H
#define IPLUGINNETWORK_H

class IPluginNetwork
{
    public:
        virtual bool    eventHandler() = 0;
        virtual void    retrievedPacket() = 0;
        virtual void    buildPacket() = 0;
};

//Q_DECLARE_INTERFACE(IPluginNetwork, "net.horus.Client.PluginNetworkInterface/1.0");

#endif // IPLUGINNETWORK_H

#ifndef IPLUGINNETWORK_H
#define IPLUGINNETWORK_H

#include <QEvent>

class IPluginNetwork
{
    public:
        virtual bool    eventHandler(QEvent *) = 0;
        virtual void    retrievedPacket() = 0;
        virtual void    buildPacket() = 0;
};

Q_DECLARE_INTERFACE(IPluginNetwork, "net.horus.Client.NetworkInterface/1.0");

#endif // IPLUGINNETWORK_H

#ifndef PLUGINNETWORK_H
#define PLUGINNETWORK_H

#include <QEvent>
#include "../../IPluginNetwork.h"

class   PluginNetwork : public IPluginNetwork
{
    public:
        PluginNetwork(QEvent *);
        bool    eventHandler();
        void    retrievedPacket();
        void    buildPacket();


    private:
        QEvent  *event;
};

#endif // PLUGINNETWORK_H

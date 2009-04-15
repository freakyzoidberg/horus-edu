#ifndef PLUGINNETWORK_H
#define PLUGINNETWORK_H

#include <QEvent>
#include <QtPlugin>
#include <QObject>
#include "../../IPluginNetwork.h"

class   PluginNetwork : public QObject, public IPluginNetwork
{
 Q_OBJECT
 Q_INTERFACES(IPluginNetwork)

public:
        PluginNetwork();
        bool    eventHandler(QEvent *);
        void    retrievedPacket();
        void    buildPacket();

};

#endif // PLUGINNETWORK_H

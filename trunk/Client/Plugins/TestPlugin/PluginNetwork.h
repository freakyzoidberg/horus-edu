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
        PluginNetwork(QEvent *);
        bool    eventHandler();
        void    retrievedPacket();
        void    buildPacket();


    private:
        QEvent  *event;
};

#endif // PLUGINNETWORK_H

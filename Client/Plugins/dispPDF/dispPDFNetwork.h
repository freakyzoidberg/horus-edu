#ifndef DISPPDFNETWORK_H
#define DISPPDFNETWORK_H

#include <QObject>
#include <QEvent>

#include <INetworkPlugin.h>

//!Implementation of the interface IPluginNetwork
class DispPDFNetwork : public QObject, public INetworkPlugin
{
 //Q_OBJECT
 //Q_INTERFACES(IPluginNetwork)

 public:
    bool    eventHandler(QEvent *);
    void    retrievedPacket();
    void    buildPacket();
};

#endif // DISPPDFNETWORK_H

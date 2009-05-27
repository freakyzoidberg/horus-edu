#ifndef DISPPDFNETWORK_H
#define DISPPDFNETWORK_H

#include <QObject>
#include <QEvent>

#include <IPluginNetwork.h>

#include <config.h>

//!Implementation of the interface IPluginNetwork
class DispPDFNetwork : public QObject, public IPluginNetwork
{

#ifndef DEBUG_VERSION
 Q_OBJECT
 Q_INTERFACES(IPluginNetwork)
#endif

 public:
    bool    eventHandler(QEvent *);
    void    retrievedPacket();
    void    buildPacket();
};

#endif // DISPPDFNETWORK_H

#ifndef DISPPDFNETWORK_H
#define DISPPDFNETWORK_H

#include <QObject>
#include <QEvent>

#include "../../IPluginNetwork.h"

//!Implementation of the interface IPluginNetwork
class DispPDFNetwork : public QObject, public IPluginNetwork
{
 Q_OBJECT
 Q_INTERFACES(IPluginNetwork)

 public:
    bool    eventHandler(QEvent *);
    void    retrievedPacket();
    void    buildPacket(void *);
};

#endif // DISPPDFNETWORK_H
